#com

import serial.tools.list_ports
import serial
from parameters import *

# Check connection
def KeepAlive():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if (port.description[:29] == DEVICE):
            return (True, port.device)
    else: return (False, NOT_FOUND)

def StartCom(x):
    return serial.Serial(x, BAUD_RATE, timeout=1)
