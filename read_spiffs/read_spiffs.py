import serial

arduino = serial.Serial(port="/dev/ttyACM1", baudrate=115200, timeout=10000)

while True:
    print(arduino.readline())
