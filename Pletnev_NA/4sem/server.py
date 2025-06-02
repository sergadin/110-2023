import socket
import subprocess
import threading
import os
import time
import signal

HOST = '127.0.0.1'
PORT = 65432
CPP_EXECUTABLE = './workload_db' # Путь к исполняемому файлу C++ бэкенда
END_MARKER = "__END_OF_CPP_OUTPUT__" # Маркер конца вывода от C++

# Глобальные переменные для управления C++ процессом и сервером
cpp_process = None
cpp_stdin = None
cpp_stdout = None
lock = threading.Lock() # Блокировка для синхронизации доступа к C++ процессу
server_running = True # Флаг для управления основным циклом сервера

# Запускает C++ бэкенд как подпроцесс
def start_cpp_process():
    global cpp_process, cpp_stdin, cpp_stdout
    if not os.access(CPP_EXECUTABLE, os.X_OK):
        print(f"FATAL ERROR: C++ executable '{CPP_EXECUTABLE}' not found or not executable.")
        return False
    print(f"Starting C++ process: {CPP_EXECUTABLE}...")
    try:
        cpp_process = subprocess.Popen(
            [CPP_EXECUTABLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            text=True, bufsize=1, universal_newlines=True
        )
        cpp_stdin = cpp_process.stdin
        cpp_stdout = cpp_process.stdout
        # cpp_stderr не используется активно для сбора ошибок в реальном времени в этой версии
        time.sleep(0.5) # Даем время на запуск
        if cpp_process.poll() is not None:
            print(f"FATAL ERROR: C++ process terminated unexpectedly after start.")
            return False
        print("C++ process started successfully.")
        return True
    except Exception as e:
        print(f"FATAL ERROR: Could not start C++ process: {e}")
        return False

# Корректно останавливает C++ подпроцесс
def stop_cpp_process():
    global cpp_process
    print("Attempting to stop C++ process...")
    if cpp_process and cpp_process.poll() is None:
        try:
            print("Sending 'exit_server_mode' to C++ process...")
            cpp_stdin.write("exit_server_mode\n")
            cpp_stdin.flush()
            cpp_process.wait(timeout=5)
            print("C++ process exited gracefully.")
        except subprocess.TimeoutExpired:
            print("C++ process did not exit gracefully, killing.")
            cpp_process.kill(); cpp_process.wait()
            print("C++ process killed.")
        except Exception as e:
            print(f"Error during C++ process shutdown: {e}")
            if cpp_process and cpp_process.poll() is None:
                cpp_process.kill(); cpp_process.wait()
                print("C++ process killed due to error during shutdown.")
    else:
        print("C++ process was not running or already terminated.")

# Отправляет команду C++ бэкенду и получает ответ
def send_command_to_cpp(command_str):
    global cpp_stdin, cpp_stdout, lock, server_running
    if not server_running: return "Server is shutting down.", ""
    if not cpp_process or cpp_process.poll() is not None:
        print("Error: C++ process is not running. Attempting to restart.")
        if not start_cpp_process(): return "FATAL: C++ process could not be restarted.", ""
    
    with lock: # Синхронизация доступа
        if not server_running: return "Server is shutting down (checked under lock).", ""
        try:
            cpp_stdin.write(command_str + "\n"); cpp_stdin.flush()
            output_buffer = []
            while server_running: # Читаем пока сервер работает
                line = cpp_stdout.readline()
                if not line: 
                    if cpp_process.poll() is not None: print("Warning: C++ process terminated while reading stdout.")
                    else: print("Warning: EOF from C++ stdout before end marker (or pipe closed).")
                    break 
                if END_MARKER in line: break # Ищем маркер конца
                output_buffer.append(line)
            if not server_running and END_MARKER not in "".join(output_buffer):
                print("Warning: Server shutdown interrupted C++ output reading.")
            # stderr C++ процесса здесь не собирается активно для простоты,
            # ошибки C++ должны выводиться им в stdout или логироваться сервером иначе.
            return "".join(output_buffer).strip(), "" 
        except BrokenPipeError:
            print("Error: Broken pipe to C++ process. It might have crashed.")
            stop_cpp_process() # Останавливаем старый процесс
            if server_running and start_cpp_process(): return "Error: C++ process crashed and was restarted. Please try again.", ""
            else: server_running = False; return "FATAL: C++ process crashed and could not be restarted.", ""
        except Exception as e:
            print(f"Error communicating with C++ process: {e}")
            if cpp_process and cpp_process.poll() is not None: # Если C++ упал
                print("C++ process seems to have terminated.")
                stop_cpp_process()
                if server_running and start_cpp_process(): return f"Error during C++ communication ({e}), process restarted. Try again.", ""
                else: server_running = False; return f"FATAL: C++ process terminated and could not be restarted after error: {e}", ""
            return f"Error: {e}", ""

# Обрабатывает одного подключенного клиента в отдельном потоке
def handle_client(conn, addr, server_socket_ref):
    global server_running
    print(f"Connected by {addr}")
    try:
        while server_running: # Работаем, пока сервер активен
            data = conn.recv(1024)
            if not data: break # Клиент отключился
            command = data.decode().strip()
            print(f"Client {addr} sent: {command}")

            if command.lower() == 'client_exit': # Команда от клиента для его отключения
                conn.sendall("Server: Closing connection.".encode()); break
            
            if command.lower() == 'shutdown_server': # Команда для остановки сервера
                if addr[0] == '127.0.0.1' or addr[0] == 'localhost': # Проверка, что команда от локального хоста
                    conn.sendall("Server: Shutdown command received. Shutting down...".encode())
                    print("Shutdown command received from client. Initiating server shutdown.")
                    server_running = False; time.sleep(0.1) # Устанавливаем флаг и даем время
                    try: # Пытаемся "разбудить" s.accept() в основном потоке
                        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ds: ds.connect((HOST, PORT)) 
                    except: pass
                    break # Завершаем этот клиентский поток
                else: conn.sendall("Server: Shutdown command allowed only from localhost.".encode()); continue
            
            stdout_res, stderr_res = send_command_to_cpp(command) # Отправляем команду в C++
            
            response = ""
            if stdout_res: response += f"{stdout_res}\n"
            if stderr_res: # Если бы мы собирали stderr отдельно
                stderr_prefix = "--- C++ Stderr ---\n" if response else ""
                response += f"{stderr_prefix}{stderr_res}\n" 
            if not response.strip(): response = "Command processed, no specific output from C++ app.\n"

            conn.sendall(response.encode())
    except ConnectionResetError: print(f"Client {addr} connection reset.")
    except Exception as e:
        if server_running: print(f"Error handling client {addr}: {e}")
    finally: print(f"Connection with {addr} closed."); conn.close()

# Обработчик сигналов для корректного завершения сервера
def signal_handler(sig, frame):
    global server_running
    print(f'\nSignal {sig} received, initiating server shutdown...')
    server_running = False
    try: # "Разбудить" s.accept()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ds: ds.settimeout(0.5); ds.connect((HOST, PORT))
    except: pass

# Основная функция запуска сервера
def main_server():
    global server_running; server_running = True
    signal.signal(signal.SIGINT, signal_handler); signal.signal(signal.SIGTERM, signal_handler)

    if not start_cpp_process(): print("Server cannot start without a C++ process."); return

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    try: server_socket.bind((HOST, PORT))
    except OSError as e: print(f"FATAL ERROR binding to {HOST}:{PORT} - {e}."); stop_cpp_process(); return
            
    server_socket.listen(); print(f"Server listening on {HOST}:{PORT}. Press Ctrl+C to stop.")
    server_socket.settimeout(1.0) # Таймаут для accept, чтобы проверять server_running

    try:
        while server_running: # Главный цикл сервера
            try:
                conn, addr = server_socket.accept()
                client_thread = threading.Thread(target=handle_client, args=(conn, addr, server_socket))
                client_thread.daemon = True; client_thread.start()
            except socket.timeout: continue # Проверяем server_running и продолжаем
            except OSError as e: 
                 if server_running: print(f"Socket error in main loop: {e}")
                 break 
            except Exception as e:
                 if server_running: print(f"Unexpected error in main server loop: {e}")
                 break
    finally:
        print("Server main loop terminated. Shutting down remaining components...")
        server_running = False; time.sleep(0.5) 
        stop_cpp_process() # Останавливаем C++ процесс
        if server_socket: server_socket.close() # Закрываем серверный сокет
        print("Server stopped completely.")

if __name__ == '__main__':
    main_server()