import socket
import subprocess
import threading
import os
import time

HOST = '127.0.0.1'
PORT = 65432
CPP_EXECUTABLE = './workload_db' 
END_MARKER = "__END_OF_CPP_OUTPUT__"
# DB_PERSIST_FILE = "persistent_database.txt" # Если C++ будет сам грузить/сохранять

cpp_process = None
cpp_stdin = None
cpp_stdout = None
cpp_stderr = None # Пока не используется активно для передачи клиенту, но можно добавить
lock = threading.Lock()

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
            stderr=subprocess.PIPE, # Перехватываем stderr C++
            text=True, # Работаем с текстом
            encoding='utf-8', # Ожидаем UTF-8 от C++
            errors='replace', # Заменяем ошибки кодировки, если C++ выводит не UTF-8
            bufsize=1, 
            universal_newlines=True 
        )
        cpp_stdin = cpp_process.stdin
        cpp_stdout = cpp_process.stdout
        cpp_stderr = cpp_process.stderr
        
        time.sleep(0.5) 
        if cpp_process.poll() is not None:
            print(f"FATAL ERROR: C++ process terminated unexpectedly after start.")
            err_out = ""
            if cpp_stderr: err_out = cpp_stderr.read()
            if err_out: print(f"--- C++ Stderr on immediate exit ---\n{err_out.strip()}")
            return False
            
        print("C++ process started successfully.")
        return True
    except Exception as e:
        print(f"FATAL ERROR: Could not start C++ process: {e}")
        return False

def send_command_to_cpp(command_str):
    global cpp_stdin, cpp_stdout, cpp_stderr, lock, cpp_process

    if not cpp_process or cpp_process.poll() is not None:
        print("Error: C++ process is not running. Attempting to restart.")
        if not start_cpp_process():
            return "FATAL: C++ process could not be restarted.", ""
    
    with lock:
        full_response = ""
        error_response = ""
        try:
            # print(f"DEBUG_SERVER: To C++: {command_str}")
            cpp_stdin.write(command_str + "\n")
            cpp_stdin.flush()

            output_buffer = []
            while True:
                line = cpp_stdout.readline()
                if not line: 
                    print("Warning: EOF from C++ stdout, process might have exited unexpectedly.")
                    # Попытка прочитать stderr, если процесс упал
                    if cpp_process.poll() is not None and cpp_stderr:
                        error_response += cpp_stderr.read()
                    break 
                if END_MARKER in line:
                    # Убираем сам маркер из строки, если он часть строки
                    line_before_marker = line.split(END_MARKER, 1)[0]
                    if line_before_marker.strip(): # Если до маркера что-то было
                        output_buffer.append(line_before_marker)
                    break
                output_buffer.append(line)
            
            full_response = "".join(output_buffer).strip()

            # Неблокирующее чтение stderr (очень упрощенно, лучше делать в отдельном потоке)
            # Но если C++ пишет ошибки и потом END_MARKER, то это не нужно.
            # Если C++ падает, poll() != None, и мы можем попытаться прочитать stderr.
            if cpp_process.poll() is not None and cpp_stderr:
                 error_response += cpp_stderr.read()


        except BrokenPipeError:
            print("Error: Broken pipe to C++ process. It might have crashed. Restarting.")
            error_response = "Error: C++ process connection lost."
            if start_cpp_process():
                 full_response = "C++ process crashed and was restarted. Please try again."
            else:
                 full_response = "FATAL: C++ process crashed and could not be restarted."
        except Exception as e:
            print(f"Error communicating with C++ process: {e}")
            error_response = f"Server error during C++ communication: {e}"
            if cpp_process and cpp_process.poll() is not None:
                print("C++ process seems to have terminated. Attempting restart.")
                if start_cpp_process():
                    full_response = f"C++ process restarted after error. Try again."
                else:
                    full_response = f"FATAL: C++ process terminated and could not be restarted."
        
        return full_response, error_response.strip()


def handle_client(conn, addr):
    print(f"Connected by {addr}")
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            command = data.decode('utf-8').strip() # Клиент шлет utf-8
            print(f"Client {addr} sent: {command}")

            final_response_to_client = ""

            if command.lower() == 'exit': # Клиент хочет выйти
                # Сервер говорит C++ процессу завершиться (если это последний клиент или по логике сервера)
                # В данном примере, команда 'exit' от клиента заставит C++ процесс выйти.
                # Это не очень хорошо для многопользовательского сервера.
                # Лучше, чтобы 'exit' от клиента просто закрывал его соединение.
                # А C++ процесс останавливался только при остановке сервера.
                #
                # Изменим: 'exit' от клиента просто закрывает его сессию.
                # C++ процесс завершается командой 'exit_server_mode' от сервера при его остановке.
                print(f"Client {addr} requested to close session.")
                final_response_to_client = "Server: Closing your session. Goodbye!"
                conn.sendall(final_response_to_client.encode('utf-8'))
                break # Выход из цикла handle_client для этого клиента

            stdout_res, stderr_res = send_command_to_cpp(command)
            
            if stdout_res:
                final_response_to_client += f"{stdout_res}\n"
            if stderr_res:
                if final_response_to_client: 
                    final_response_to_client += f"--- C++ Errors/Warnings ---\n"
                final_response_to_client += f"{stderr_res}\n"
            
            if not final_response_to_client.strip():
                final_response_to_client = "Command processed by C++ app, no specific output.\n"

            conn.sendall(final_response_to_client.encode('utf-8'))
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
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
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
                client_thread.daemon = True 
                client_thread.start()
        except KeyboardInterrupt:
            print("\nServer shutting down by user interrupt (Ctrl+C)...")
        finally:
            print("Closing C++ process...")
            if cpp_process and cpp_process.poll() is None:
                try:
                    # Посылаем команду для корректного завершения C++
                    # (C++ main должен обработать "exit_server_mode")
                    cpp_stdin.write("exit_server_mode\n") 
                    cpp_stdin.flush()
                    cpp_process.wait(timeout=5)
                    print("C++ process exited via command.")
                except subprocess.TimeoutExpired:
                    print("C++ process did not exit via command, killing.")
                    cpp_process.kill()
                    cpp_process.wait()
                except Exception as e:
                    print(f"Error sending exit_server_mode or waiting for C++ process: {e}")
                    if cpp_process and cpp_process.poll() is None:
                        cpp_process.kill()
                        cpp_process.wait()
            
            # Попытка прочитать остатки stderr после завершения
            if cpp_stderr and not cpp_stderr.closed:
                try:
                    remaining_err = cpp_stderr.read()
                    if remaining_err:
                        print(f"--- Remaining C++ Stderr on shutdown ---\n{remaining_err.strip()}")
                except:
                    pass # Игнорируем ошибки чтения из уже закрытого потока

            print("Server stopped.")

if __name__ == '__main__':
    main_server()