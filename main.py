import serial
import time

def main():
    arduino = serial.Serial('COM7', 9600, timeout = 1)
    
    while(True):
        inp = input()
        if(inp[0] == "C"):
            inp = "C" + str(int(inp[1:], 16))
        # print(bytes(hex, 'utf-8'))
        arduino.write(bytes(inp, 'utf-8'))
        print(arduino.readline())
if __name__ == "__main__":
    main()