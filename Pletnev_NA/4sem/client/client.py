import socket
import time

HOST = '127.0.0.1'
PORT = 65432
SERVER_ADDRESS = (HOST, PORT)

def main():
    print("=== Client for University Workload Database ===")
    print("Type C++ app commands, or 'client_exit' to disconnect.")

    while True: # Основной цикл для попыток переподключения
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                print(f"Attempting to connect to server at {HOST}:{PORT}...")
                s.connect(SERVER_ADDRESS)
                print(f"Connected to server.")

                while True: # Цикл общения с сервером
                    command = input("client> ")
                    if not command.strip():
                        continue

                    s.sendall(command.encode())

                    if command.strip().lower() == 'client_exit':
                        print("Sent exit request to server...")
                        response_data = s.recv(4096) 
                        print(f"Server: {response_data.decode().strip()}")
                        print("Client session ended by 'client_exit'.")
                        return # Выход из main()

                    response_parts = []
                    while True: # Читаем ответ, пока есть данные или не произойдет таймаут
                        try:
                            s.settimeout(2.0) # Таймаут на чтение, чтобы не висеть вечно
                            chunk = s.recv(4096)
                            s.settimeout(None) # Сброс таймаута
                            if not chunk: # Сервер закрыл соединение (или часть ответа)
                                break
                            response_parts.append(chunk.decode())
                            # Если мы ожидаем маркер конца ответа от сервера, проверяем здесь
                            # Но C++ маркер __END_OF_CPP_OUTPUT__ обрабатывается сервером Python.
                            # Сервер Python должен отправить все сразу или частями.
                            # Для простоты, если получили меньше, чем ожидали, возможно, это все.
                            if len(chunk) < 4096 : # Упрощенное условие конца сообщения
                                break
                        except socket.timeout:
                            # print("Socket timeout waiting for more data from server.")
                            break # Выходим из цикла чтения, если данных больше нет
                    
                    response_str = "".join(response_parts).strip()
                    print(f"\n--- Server Response ---\n{response_str}\n-----------------------\n")

        except ConnectionRefusedError:
            print(f"Connection refused. Server at {HOST}:{PORT} might not be running. Retrying in 5 seconds...")
            time.sleep(5)
        except ConnectionResetError:
            print("Connection to server lost. Retrying in 5 seconds...")
            time.sleep(5)
        except BrokenPipeError:
            print("Connection to server broken. Retrying in 5 seconds...")
            time.sleep(5)
        except KeyboardInterrupt:
            print("\nExiting client by user interrupt (Ctrl+C).")
            # Попытка отправить 'client_exit' не всегда сработает здесь, т.к. сокет может быть уже закрыт
            return # Выход из main()
        except Exception as e:
            print(f"An error occurred: {e}. Retrying in 5 seconds...")
            time.sleep(5)

if __name__ == '__main__':
    main()