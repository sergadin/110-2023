import socket
import time

HOST = '127.0.0.1'  # IP-адрес сервера (localhost)
PORT = 65432        # Порт сервера (должен совпадать с серверным)
SERVER_ADDRESS = (HOST, PORT)

# Выводит начальную информацию для пользователя клиента
def print_initial_client_info():
    print("=== Client for University Workload Database ===")
    print("Type 'help' to get a list of available C++ application commands from the server.")
    print("Type 'exit' to disconnect from server and exit client.") 
    print("Type 'shutdown_server' to request server shutdown (from localhost only).")
    print("-" * 50)

# Основная функция клиента
def main():
    print_initial_client_info()

    while True: # Внешний цикл для попыток переподключения
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: # Создаем сокет
                print(f"Attempting to connect to server at {HOST}:{PORT}...")
                s.connect(SERVER_ADDRESS) # Подключаемся к серверу
                print(f"Connected to server.")

                while True: # Внутренний цикл для общения с сервером после подключения
                    command = input("client> ") # Читаем команду от пользователя
                    if not command.strip(): # Пропускаем пустые команды
                        continue
                    
                    s.sendall(command.encode('utf-8')) # Отправляем команду серверу в UTF-8
                    command_lower = command.strip().lower()

                    # Обработка локальных команд клиента или команд, требующих особого поведения
                    if command_lower == 'exit': # Команда для завершения сессии этого клиента
                        print("Sent 'exit' command to server...")
                        try:
                            s.settimeout(3.0)
                            response_data = s.recv(4096) 
                            print(f"Server: {response_data.decode('utf-8', errors='replace').strip()}")
                        except socket.timeout: print("Timeout waiting for server ACK on exit.")
                        except Exception as e_ack: print(f"Error receiving ACK on exit: {e_ack}")
                        print("Client session should be closed by server. Exiting client.")
                        return # Выход из функции main, завершение клиента
                    
                    if command_lower == 'shutdown_server': # Команда для запроса остановки сервера
                        print("Sent shutdown request to server...")
                        try:
                            s.settimeout(5.0)
                            response_data = s.recv(4096) 
                            print(f"Server: {response_data.decode('utf-8', errors='replace').strip()}")
                            if "Shutting down" in response_data.decode('utf-8', errors='replace'):
                                print("Server is shutting down. Exiting client.")
                                return 
                        except socket.timeout: print("No specific confirmation from server on shutdown, command sent."); return 
                        except Exception as e: print(f"Error or server closed connection after shutdown command: {e}"); return 
                    
                    # Получение ответа от сервера
                    full_response_bytes = b''
                    while True: # Читаем ответ частями, пока есть данные или не сработает таймаут
                        try:
                            s.settimeout(0.5) # Короткий таймаут для каждого чанка
                            chunk = s.recv(4096)
                            if not chunk: break # Сервер закрыл соединение или больше нет данных
                            full_response_bytes += chunk
                            # Простое условие выхода, если пришло меньше, чем размер буфера
                            if len(chunk) < 4096 : break 
                        except socket.timeout: break # Данных больше нет
                        except Exception as e_recv: print(f"Error during recv: {e_recv}"); break
                    
                    s.settimeout(None) # Сбрасываем таймаут для сокета
                    response_str = ""
                    if full_response_bytes:
                        try: response_str = full_response_bytes.decode('utf-8')
                        except UnicodeDecodeError as ude:
                            print(f"UnicodeDecodeError: {ude}. Trying 'replace' errors.")
                            response_str = full_response_bytes.decode('utf-8', errors='replace')
                    
                    response_str = response_str.strip()
                    if response_str: print(f"\n--- Server Response ---\n{response_str}\n-----------------------\n")
                    else: print(f"\n--- Server Response ---\n(No specific text content received or decode error)\n-----------------------\n")

        # Обработка ошибок соединения и других исключений
        except ConnectionRefusedError: print(f"Connection refused. Server at {HOST}:{PORT} might not be running. Retrying in 5s..."); time.sleep(5)
        except (ConnectionResetError, BrokenPipeError) as e_conn: print(f"Connection to server lost/broken: {e_conn}. Retrying in 5s..."); time.sleep(5)
        except KeyboardInterrupt: print("\nExiting client by Ctrl+C."); return 
        except Exception as e: print(f"An unexpected error occurred: {e}. Retrying in 5s..."); time.sleep(5)

if __name__ == '__main__':
    main()