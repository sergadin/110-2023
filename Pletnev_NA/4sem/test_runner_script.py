import socket
import sys
import time
import uuid

SERVER_HOST = '127.0.0.1'
SERVER_PORT = 65432

def execute_commands(command_file, client_id_prefix="Client", delay_ms=0):
    client_unique_id = f"{client_id_prefix}_{str(uuid.uuid4())[:4]}"
    all_responses = [] # Будем собирать все ответы

    print(f"--- Starting {client_unique_id} with commands from {command_file} ---")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((SERVER_HOST, SERVER_PORT))
            print(f"[{client_unique_id}] Connected to server.")
        except Exception as e:
            print(f"[{client_unique_id}] FAILED to connect: {e}")
            all_responses.append(f"CONNECT_FAIL: {e}")
            return all_responses # Возвращаем собранные ответы/ошибки

        command_counter = 0
        try:
            with open(command_file, 'r') as f:
                for line in f:
                    command = line.strip()
                    if not command or command.startswith('#'):
                        continue

                    command_counter += 1
                    request_id = f"[{client_unique_id}-CMD-{command_counter:02d}]"
                    
                    print(f"{request_id} Sending: {command}")
                    s.sendall(command.encode('utf-8'))
                    
                    response_parts = []
                    s.settimeout(5.0) 
                    try:
                        while True:
                            chunk = s.recv(4096)
                            if not chunk: break
                            response_parts.append(chunk.decode('utf-8', errors='replace'))
                            if len(chunk) < 4096: break 
                    except socket.timeout:
                        print(f"{request_id} Socket timeout waiting for response.")
                        response_parts.append("TIMEOUT_ERROR")
                    except Exception as e_recv:
                        print(f"{request_id} Error receiving data: {e_recv}")
                        response_parts.append(f"RECV_ERROR: {e_recv}")
                    
                    response_str = "".join(response_parts).strip()
                    print(f"{request_id} Response:\n---\n{response_str}\n---\n")
                    all_responses.append({
                        "request_id": request_id,
                        "command": command,
                        "response": response_str
                    })
                    
                    if delay_ms > 0:
                        time.sleep(delay_ms / 1000.0)

            print(f"[{client_unique_id}] All commands from {command_file} sent.")
            s.sendall("client_exit".encode('utf-8'))
            try:
                s.settimeout(2.0)
                final_ack = s.recv(1024)
                ack_msg = final_ack.decode('utf-8', errors='replace').strip()
                print(f"[{client_unique_id}] Server ACK on exit: {ack_msg}")
                all_responses.append({"event": "client_exit_ack", "ack": ack_msg})
            except socket.timeout:
                print(f"[{client_unique_id}] Timeout waiting for server ACK on exit.")
                all_responses.append({"event": "client_exit_ack_timeout"})
            except Exception as e_ack:
                 print(f"[{client_unique_id}] Error on client_exit ACK: {e_ack}")
                 all_responses.append({"event": "client_exit_ack_error", "error": str(e_ack)})


        except FileNotFoundError:
            error_msg = f"Error: Command file '{command_file}' not found."
            print(f"[{client_unique_id}] {error_msg}")
            all_responses.append({"error": error_msg})
        except Exception as e:
            error_msg = f"Error during client ({client_unique_id}) execution: {e}"
            print(error_msg)
            all_responses.append({"error": error_msg})
        finally:
            print(f"[{client_unique_id}] Disconnecting.")
            print(f"--- Finished {client_unique_id} ---")
        
        return all_responses


if __name__ == "__main__":
    # Этот блок позволяет запускать скрипт напрямую для одного файла команд
    if len(sys.argv) < 2:
        print("Usage: python3 test_runner_script.py <command_file.txt> [client_id_prefix] [delay_ms]")
        sys.exit(1)

    cmd_file = sys.argv[1]
    client_prefix = sys.argv[2] if len(sys.argv) > 2 else "DirectRunClient"
    cmd_delay_ms = int(sys.argv[3]) if len(sys.argv) > 3 else 0
    
    execute_commands(cmd_file, client_prefix, cmd_delay_ms)