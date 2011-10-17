import serial

def string_to_integer(chr_bytes):
    
    # muda o tipo de char pra inteiro
    int_bytes = []
    for i in xrange(4):
        int_bytes.append(ord(chr_bytes[i]))
    
    # montagem do inteiro de 4 bytes
    integer = int_bytes[3] << 24 | int_bytes[2] << 16 | int_bytes[1] << 8 | int_bytes[0]
    
    return integer

def read_4_bytes():
    serial_conn = serial.Serial('/dev/ttyUSB0', 115200)

    bytes = []
    for i in xrange(4):
        bytes.append(serial_conn.read())

    serial_conn.close()

    return string_to_integer(bytes)

def add(a,b):
    return "%d + %d = %d"%(a,b,(a+b))

