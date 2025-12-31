import paho.mqtt.client as mqtt
import struct
import datetime

BROKER = "192.168.0.127"   # change to your broker address
PORT = 1883
TOPIC = "/topic/qos1"
counter = 0

# Callback when connected to the broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected successfully")
        client.subscribe(TOPIC, qos=1)
        print(f"Subscribed to {TOPIC} with QoS 1")
    else:
        print(f"Connection failed with code {rc}")

# Callback when a message is received
def on_message(client, userdata, msg):
    global counter
    #print(f"Received message on {msg.topic}")
    #print(f"QoS: {msg.qos}")

    #print("Raw bytes:", msg.payload.hex())
    try:
        # Decode 4 bytes as float (little-endian)
        gas_res = struct.unpack("<f", msg.payload[:4])[0]
        humid = struct.unpack("<f", msg.payload[3:8])[0]
        temp = struct.unpack("<f", msg.payload[7:12])[0]
        press = struct.unpack("<f", msg.payload[11:16])[0]
        if(counter > 100):
            print("Alive ", datetime.datetime.now(), value)
            counter = 0
        counter += 1
        with open("logs/log3.log", "a") as f:
            f.write(str(datetime.datetime.now()))
            f.write(";")
            f.write(str(gas_res))
            f.write(";")
            f.write(str(humid))
            f.write(";")
            f.write(str(temp))
            f.write(";")
            f.write(str(press))
            f.write("\n")

    except struct.error as e:
        print("Failed to decode payload:", e)
#    print(f"Payload: {msg.payload.decode()}")

def main():
    # Create MQTT client
    client = mqtt.Client()

    # Assign callbacks
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to broker
    client.connect(BROKER, PORT, keepalive=60)

    # Start network loop (blocking)
    client.loop_forever()

if __name__ == '__main__':
    main()
