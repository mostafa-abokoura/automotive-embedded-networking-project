import wx, serial, time
import serial.tools.list_ports


DEVICE = "Stellaris Virtual Serial Port"
NOT_FOUND = "COM!"
BAUD_RATE = 115200

def KeepAlive():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if (port.description[:29] == DEVICE):
            return (True, port.device)
    else: return (False, NOT_FOUND)

    
serEstablished = False
serErrorRepeat = False

print(KeepAlive())

counter = 0

while True:
    serState = KeepAlive()
    if serState[0] == True:
        if serEstablished and serErrorRepeat:
            serErrorRepeat = False
            ser.close()
            ser.open()
        if not serEstablished:
            serEstablished = True
            ser = serial.Serial(serState[1], BAUD_RATE, timeout=1)
        char = ser.read().decode("utf-8")
        if (char == '\n'):
            counter += 1
            print('{:5d}'.format(counter), ": CMD = ", end='')
        elif (char != '\r'):
            if (char != '!'):
                print(char, end='')
            else:
                print()
    else:
        if not serErrorRepeat:
            serErrorRepeat = True
            print("Make sure TIVA-C is connected!")
