import threading
import time
from test_runner_script import execute_commands # Импортируем функцию

# Файлы команд для каждого клиента
client2_command_file = "test2.txt"
client3_command_file = "test3.txt"

# Задержки между командами для каждого клиента (в миллисекундах)
client2_delay = 30 # мс
client3_delay = 45 # мс

def run_client_task(command_file, client_id_prefix, delay):
    print(f"Starting task for {client_id_prefix} with file {command_file}")
    responses = execute_commands(command_file, client_id_prefix, delay)

    print(f"Finished task for {client_id_prefix}")

if __name__ == "__main__":
    print("Starting concurrent client tests...")
    print("Make sure server.py is running!")
    print("-" * 30)

    # Создаем потоки для каждого клиента
    thread2 = threading.Thread(target=run_client_task, args=(client2_command_file, "Client2", client2_delay))
    thread3 = threading.Thread(target=run_client_task, args=(client3_command_file, "Client3", client3_delay))

    # Запускаем потоки
    thread2.start()
    time.sleep(0.01) # Небольшая задержка между запусками потоков, чтобы они не стартовали абсолютно в один такт
    thread3.start()

    # Ждем завершения обоих потоков
    thread2.join()
    thread3.join()

    print("-" * 30)
    print("Concurrent client tests finished.")
    print("Check server logs and saved files (db_after_client2.txt, db_after_client3.txt) for results.")