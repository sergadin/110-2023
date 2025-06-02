import socket
import time

HOST = '127.0.0.1'
PORT = 65432
SERVER_ADDRESS = (HOST, PORT)

def print_initial_client_info():
    print("=== Client for University Workload Database ===")
    print("Type 'help' to get a list of available C++ application commands from the server.")
    print("Type 'exit' to disconnect from server and exit client.") # Изменено с client_exit
    print("-" * 50)

def main():
    print_initial_client_info()

    while True: 
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                print(f"Attempting to connect to server at {HOST}:{PORT}...")
                s.connect(SERVER_ADDRESS)
                print(f"Connected to server.")

                # Автоматический запрос help при подключении (опционально)
                # print("Automatically fetching help from server...")
                # s.sendall("help".encode('utf-8'))
                # initial_help_parts = []
                # # ... (логика чтения ответа для help) ...
                # print(f"\n--- Server Help Response ---\n{''.join(initial_help_parts).strip()}\n--------------------------\n")


                while True: 
                    command = input("client> ")
                    if not command.strip():
                        continue
                    
                    s.sendall(command.encode('utf-8')) # Отправляем в UTF-8

                    if command.strip().lower() == 'exit': # Теперь это команда для сервера
                        print("Sent 'exit' command to server (to close this client's session)...")
                        # Сервер должен ответить и закрыть соединение для этого клиента
                        # C++ процесс продолжит работать для других клиентов.
                        # Если 'exit' должен останавливать C++ процесс, то это логика сервера.
                        # В текущем server.py 'exit' от клиента просто закрывает сессию клиента.
                        try:
                            s.settimeout(3.0)
                            response_data = s.recv(4096) 
                            print(f"Server: {response_data.decode('utf-8', errors='replace').strip()}")
                        except socket.timeout:
                            print("Timeout waiting for server ACK on exit.")
                        except Exception as e_ack:
                            print(f"Error receiving ACK on exit: {e_ack}")
                        print("Client session should be closed by server. Exiting client.")
                        return 

                    response_parts = []
                    while True: 
                        try:
                            s.settimeout(3.0) 
                            chunk = s.recv(4096)
                            s.settimeout(None) 
                            if not chunk: 
                                break
                            response_parts.append(chunk.decode('utf-8', errors='replace'))
                            if len(chunk) < 4096 : 
                                break
                        except socket.timeout:
                            # print("DEBUG_CLIENT: Socket timeout waiting for more data.")
                            break 
                    
                    response_str = "".join(response_parts).strip()
                    if response_str: # Печатаем, только если есть что печатать
                        print(f"\n--- Server Response ---\n{response_str}\n-----------------------\n")
                    else:
                        print(f"\n--- Server Response ---\n(No specific text content received)\n-----------------------\n")


        except ConnectionRefusedError:
            print(f"Connection refused. Server at {HOST}:{PORT} might not be running. Will retry in 5 seconds...")
            time.sleep(5)
        except (ConnectionResetError, BrokenPipeError) as e_conn:
            print(f"Connection to server lost or broken: {e_conn}. Will retry in 5 seconds...")
            time.sleep(5)
        except KeyboardInterrupt:
            print("\nExiting client by user interrupt (Ctrl+C).")
            # Здесь можно попытаться отправить 'exit' серверу, если сокет 's' еще инициализирован и открыт
            # но это не всегда надежно при Ctrl+C.
            return 
        except Exception as e:
            print(f"An unexpected error occurred: {e}. Will retry in 5 seconds...")
            time.sleep(5)
            
    # print("Client has shut down.") # Этот вывод не будет достигнут из-за return в KeyboardInterrupt

if __name__ == '__main__':
    main()