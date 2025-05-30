import asyncio
from bleak import BleakClient, BleakScanner

#SERVICE_UUID = "180C"
CHAR_UUID = "2A56"
address = "5B:86:37:1F:4E:7F" # Arduino Nano 33 BLE Rev3 MAC Address

def handle_notification(sender, data):
    try:
        print(f"EMG: {data.decode().strip()}")
    except Exception as e:
        print(f"Error decoding data: {e}")

async def main():
    async with BleakClient(address) as client:
        print("Connecting...")

        if not client.is_connected:
            print("Failed to connect.")
            return

        print(f"Connected to {address}. Streaming data...")
        
        # Start receiving notifications from Arduino
        await client.start_notify(CHAR_UUID, handle_notification)
#        value = await client.read_gatt_char(CHAR_UUID)
#        print("Received: ", value.decode())
        
        # Keep the program running while connected
        try:
            while client.is_connected:
                await asyncio.sleep(1)
        except KeyboardInterrupt:
            print("interrupted by user.")
        finally:
            await client.stop_notify(CHAR_UUID)
            print("Disconnected.")


#def handle_notification(sender, data):
#    print(f"Received from Arduino: {data.decode()}")
#
#async def main():
#    print("Scanning for devices...")
#    devices = await BleakScanner.discover()
#    nano = next((d for d in devices if "Nano33BLE" in d.name), None)
#
#    if not nano:
#        print("Nano33BLE not found!")
#        return
#
#    async with BleakClient(nano.address) as client:
#        print(f"Connected to {nano.name}")
#        await client.start_notify(CHAR_UUID, handle_notification)
#
#        print("Listening for BLE messages for 30 seconds...")
#        await asyncio.sleep(30)
#
#        await client.stop_notify(CHAR_UUID)
#        print("Disconnected.")
#
asyncio.run(main())

