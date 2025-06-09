import socket
import time
import random
# import serial
# from dest_disp_ble import get_x, handle_notification
import asyncio
from bleak import BleakClient, BleakScanner

# random is for simulated values
# need to update with actual emg processing

HOST = '127.0.0.1'
PORT = 5005
CHAR_UUID = "2A56"
address = "dc:da:0c:21:5b:09" # MAC Address
# ser = serial.Serial('COM10', 115200)  # Replace COM3 with your Arduino port and baud rate

def get_emg_values():
    pec = random.uniform(0,1)
    rhomboid = random.uniform(0,1)
    deltoid = random.uniform(0,1)
    return pec, rhomboid, deltoid

# angle_x = 0
# angle_y = 0

while True:
    try:
        angle_x = 0
        angle_y = get_emg_values()

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            message = f"{angle_x:.2f},{angle_y:.2f}\n"
            s.sendall(message.encode('utf-8'))
            print(f"Sent: {message.strip()}")

        time.sleep(1) 
    except Exception as e:
        print("Error:", e)
        time.sleep(1)

# def handle_notification(sender, data):
#     global angle_y
#     try:
#         angle_y = float(data.decode().strip())
#         print(f"Received: {angle_y}")
#     except Exception as e:
#         print(f"Notification error: {e}")

# async def ble_loop():
#     async with BleakClient(address) as client:
#         print("Connecting to BLE...")
#         await client.start_notify(CHAR_UUID, handle_notification)
#         print("BLE connected. Receiving notifications...")
#         while client.is_connected:
#             await asyncio.sleep(0.1)  # Keep BLE alive

# async def socket_loop():
#     global angle_x, angle_y
#     while True:
#         try:
#             with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#                 s.connect((HOST, PORT))
#                 message = f"{angle_x:.2f},{angle_y:.2f}\n"
#                 s.sendall(message.encode())
#                 print(f"Sent: {message.strip()}")
#         except Exception as e:
#             print("Socket error:", e)
#         await asyncio.sleep(0.2)  # 5Hz update

# async def main():
#     await asyncio.gather(
#         ble_loop(),
#         socket_loop()
#     )

# if __name__ == "__main__":
#     asyncio.run(main())