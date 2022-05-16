import serial.tools.list_ports
import sys

SERIAL_OK = b'OK\n'
SERIAL_ERROR = b'ERROR\n'


def get_stm_port():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if port.description.find("STM") != -1:
            return port.device

    return -1


def open_serial(port, baudrate = 115200, timeout = 2.0) -> serial:
    try:
        ser = serial.Serial()
        ser.port = port
        ser.baudrate = baudrate
        ser.timeout = timeout
        ser.open()
    except Exception as e:
        print("Connection error: ", e.__class__)

    return ser


def serial_transmit(ser: serial, buf: str):
    if buf[-1] != "\n":
        buf += "\n"
    str_buf_len = str(len(buf))
    if len(str_buf_len) == 1:
        str_buf_len = '0' + str_buf_len
    elif len(str_buf_len) > 2:
        return bytearray()

    if ser.is_open:
        ser.write(str_buf_len.encode())
        b_read = ser.read_until()
        if b_read == SERIAL_OK:
            ser.write(buf.encode())
            b_read = ser.read_until()
            if b_read == SERIAL_OK:
                return ser.read_until()
    return bytearray()


s = open_serial(get_stm_port())
serial_transmit(s, "GET_TIME")
