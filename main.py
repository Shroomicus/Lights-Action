import serial
import time

def main():
    arduino = serial.Serial('COM7', 9600, timeout = 1)
    hex = "C" + str(int("940303", 16))
    print(bytes(hex, 'utf-8'))
    arduino.write(bytes(hex, 'utf-8'))
    while(True):
        print(arduino.readline())
if __name__ == "__main__":
    main()