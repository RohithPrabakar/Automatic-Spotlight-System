import serial
import time
# make sure the 'COM#' is comms ardriuno coonected to  
ser = serial.Serial('COM7', 9800)
time.sleep(2)

group = []
window_size = 7
weighted_data = 0
or_data = 0

while(True):
    data = []
    b = ser.readline()
    string_n = b.decode()
    string = string_n.rstrip()
    x = string.split(',')
    for i in x:
        data.append(int(i))
    print(data)
    

