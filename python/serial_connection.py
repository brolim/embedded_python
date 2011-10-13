import serial
import os
from ctypes import CDLL, c_char_p

def parse_str2int(chr_bytes):
    
    # muda o tipo de char pra inteiro
    int_bytes = []
    for i in xrange(4):
        int_bytes.append(ord(chr_bytes[i]))
    
    # montagem do inteiro de 4 bytes
    integer = int_bytes[3] << 24 | int_bytes[2] << 16 | int_bytes[1] << 8 | int_bytes[0]
    
    return integer

def open_serial():
    ser = serial.Serial('/dev/ttyUSB0', 115200)
    return ser

def read_integer(serial_conn):
    bytes = []

    for i in xrange(4):
        bytes.append(serial_conn.read())

    return parse_str2int(bytes)
    
if __name__ == '__main__':
    ser = open_serial()
    number = read_integer(ser)

    getenv = CDLL("libc.so.6").getenv
    getenv.restype = c_char_p
    print getenv("HOME")


    print "\n\nlah vem o echo no python"
    os.system("echo $KAR_NUMBER")
    print "cabou o python\n\n"
    

