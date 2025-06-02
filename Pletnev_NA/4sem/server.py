import socket
import subprocess
import threading
import os
import time

HOST = '127.0.0.1'
PORT = 65432
CPP_EXECUTABLE = './workload_db' # Убедитесь, что путь правильный
END_MARKER = "__END_OF_CPP_OUTPUT__"
DB_FILE = "persistent_database.txt" # Файл для сохранения/загрузки состояния

cpp_process = None
cpp_stdin = None
cpp_stdout = None
cpp_stderr = None
lock = threading.Lock() # Блокировка для синхронизации доступа к C++ процессу

def start_cpp_process():
    global cpp_process, cpp_stdin, cpp_stdout, cpp_stderr
    if not os.access(CPP_EXECUTABLE, os.X_OK):
        print(f"FATAL ERROR: C++ executable '{CPP_EXECUTABLE}' not found or not executable.")
        return False

    print(f"Starting C++ process: {CPP_EXECUTABLE}...")
    try:
        cpp_process = subprocess.Popen(
            [CPP_EXECUTABLE],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1, 
            universal_newlines=True
        )
        cpp_stdin = cpp_process.stdin
        cpp_stdout = cpp_process.stdout
        cpp_stderr = cpp_process.stderr
        
        time.sleep(0.5)
        if cpp_process.poll() is not None: # Процесс завершился сразу
            print(f"FATAL ERROR: C++ process terminated unexpectedly after start.")
            print_cpp_errors()
            return False
            
        print("C++ process started successfully.")
        return True
    except Exception as e:
        print(f"FATAL ERROR: Could not start C++ process: {e}")
        return False

def print_cpp_errors():
    global cpp_stderr
    if cpp_stderr:
        try:
            time.sleep(0.1) # Даем время на запись в stderr
            if cpp_stderr.readable():
                 if cpp_process and cpp_process.poll() is not None:
                    err_output = cpp_process.stderr.read()
                    if err_output:
                        print(f"--- C++ Stderr (on process exit/error) ---\n{err_output.strip()}")
        except Exception as e:
            print(f"Error reading C++ stderr: {e}")


def send_command_to_cpp(command_str):
    global cpp_stdin, cpp_stdout, cpp_stderr, lock

    if not cpp_process or cpp_process.poll() is not None:
        print("Error: C++ process is not running. Attempting to restart.")
        if not start_cpp_process():
            return "FATAL: C++ process could not be restarted.", ""
    
    with lock: # Синхронизируем доступ к C++ процессу
        try:
            # print(f"To C++: {command_str}") # Для отладки
            cpp_stdin.write(command_str + "\n")
            cpp_stdin.flush()

            output_buffer = []
            error_buffer = []
            
            # Чтение stdout до маркера
            while True:
                line = cpp_stdout.readline()
                if not line: # EOF или ошибка
                    # print("Warning: EOF from C++ stdout before end marker.")
                    break 
                if END_MARKER in line:
                    # print(f"Got END_MARKER from C++ stdout") # Для отладки
                    break
                output_buffer.append(line)

            time.sleep(0.01) # Короткая пауза
            if cpp_process.poll() is not None:
                err_output = cpp_stderr.read() # Читаем все, что есть, если процесс упал
                if err_output:
                    error_buffer.append(err_output)
            
            stdout_data = "".join(output_buffer).strip()
            stderr_data = "".join(error_buffer).strip()

            return stdout_data, stderr_data

        except BrokenPipeError:
            print("Error: Broken pipe to C++ process. It might have crashed. Restarting.")
            if start_cpp_process():
                 return "Error: C++ process crashed and was restarted. Please try again.", ""
            else:
                 return "FATAL: C++ process crashed and could not be restarted.", ""
        except Exception as e:
            print(f"Error communicating with C++ process: {e}")
            # Попытка перезапуска, если процесс упал
            if cpp_process and cpp_process.poll() is not None:
                print("C++ process seems to have terminated. Attempting restart.")
                if start_cpp_process():
                    return f"Error during C++ communication ({e}), process restarted. Try again.", ""
                else:
                    return f"FATAL: C++ process terminated and could not be restarted after error: {e}", ""
            return f"Error: {e}", ""


def handle_client(conn, addr):
    print(f"Connected by {addr}")
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            command = data.decode().strip()
            print(f"Client {addr} sent: {command}")

            if command.lower() == 'client_exit':
                conn.sendall("Server: Closing connection.".encode())
                break

            stdout_res, stderr_res = send_command_to_cpp(command)
            
            response = ""
            if stdout_res:
                response += f"{stdout_res}\n"
            if stderr_res: # Добавляем ошибки C++ в ответ
                if response: # Если уже был stdout, добавляем разделитель
                    response += f"--- C++ Stderr ---\n"
                response += f"{stderr_res}\n"
            
            if not response.strip():
                response = "Command processed, no specific output from C++ app.\n"

            conn.sendall(response.encode())
    except ConnectionResetError:
        print(f"Client {addr} connection reset.")
    except Exception as e:
        print(f"Error handling client {addr}: {e}")
    finally:
        print(f"Connection with {addr} closed.")
        conn.close()

def main_server():
    if not start_cpp_process():
        print("Server cannot start without a C++ process.")
        return

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # Разрешаем переиспользование адреса
        try:
            s.bind((HOST, PORT))
        except OSError as e:
            print(f"FATAL ERROR binding to {HOST}:{PORT} - {e}. Port might be in use.")
            return
            
        s.listen()
        print(f"Server listening on {HOST}:{PORT}")

        try:
            while True:
                conn, addr = s.accept()
                client_thread = threading.Thread(target=handle_client, args=(conn, addr))
                client_thread.daemon = True # Потоки завершатся, когда завершится основной
                client_thread.start()
        except KeyboardInterrupt:
            print("\nServer shutting down by user interrupt (Ctrl+C)...")
        finally:
            print("Closing C++ process...")
            if cpp_process and cpp_process.poll() is None: # Если процесс еще жив
                try:
                    # Попытка корректного завершения C++
                    # send_command_to_cpp(f"save {DB_FILE}") # Сохраняем перед выходом
                    send_command_to_cpp("exit_server_mode") 
                    cpp_process.wait(timeout=5) # Ждем завершения
                except subprocess.TimeoutExpired:
                    print("C++ process did not exit gracefully, killing.")
                    cpp_process.kill()
                except Exception as e:
                    print(f"Error during C++ process shutdown: {e}")
                    if cpp_process and cpp_process.poll() is None:
                        cpp_process.kill() # Принудительное завершение в случае ошибки
            print_cpp_errors() # Показать ошибки, если были при завершении
            print("Server stopped.")


if __name__ == '__main__':
    main_server()