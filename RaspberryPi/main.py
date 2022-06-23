from digi.xbee.devices import XBeeDevice
from paho import mqtt
import paho.mqtt.client as paho
import time
import random  # hostname
import datetime

xbee = XBeeDevice("/dev/ttyUSB0", 9600)
xbee.open()

broker = "localhost"  # port
port = 1883
client = paho.Client(client_id="client", userdata=None, protocol=paho.MQTTv5)

def on_publish(client, userdata, result):
    print("Device 1 : Data published.")
    passclient = paho.Client("admin")

client.on_publish = on_publish
client.connect(broker, port)

while 1 == 1:
    # Read data.
    xbee_message = xbee.read_data()
    if(xbee_message != None):
        # telemetry to send
        x = datetime.datetime.now()
        message = (x.strftime("%x") + x.strftime(" %X : Person entered the room!"))
        # publish message
        ret = client.publish("mqtt/test", message)