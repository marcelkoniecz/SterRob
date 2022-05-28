import database_operations as db
import serial_port as sp
import measurements_operations as mo
import serial.tools.list_ports


def receive_all_measurements(ser: serial):
    try:
        meas_list = []

        if sp.serial_transmit(ser, "GET_ALL_MEAS") == sp.SERIAL_OK:
            while True:
                row = sp.serial_receive(ser)
                if len(row) == 0:
                    return None
                elif row == sp.SERIAL_OK:
                    return meas_list
                elif row == sp.SERIAL_ERROR:
                    return None
                else:
                    val_list = row.decode("utf-8")
                    val_list = val_list[:-2]
                    val_list = val_list.split(";")

                    temp_list = []
                    for i in range(1, len(val_list)):
                        temp_list.append(int(val_list[i]))

                    meas_list.append(mo.Measurement(int(val_list[0]), temp_list))

    except Exception as e:
        print("Connection error: ", e.__class__)
        return None


def set_time(ser: serial, timestamp: int) -> bool:
    try:
        if timestamp < 0:
            return True
        if sp.serial_transmit(ser, "SET_TIME" + str(timestamp)) != sp.SERIAL_OK:
            return True
        if sp.serial_receive(ser) != sp.SERIAL_OK:
            return True
    except Exception as e:
        print("Connection error: ", e.__class__)
        return True

    return False


def get_time(ser: serial) -> int:
    try:
        if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
            return None
        timestamp = sp.serial_receive(ser)
        if len(timestamp) == 0:
            return None
        resp = sp.serial_receive(ser)
        if resp != sp.SERIAL_OK:
            return None

    except Exception as e:
        print("Connection error: ", e.__class__)
        return None

    return int(timestamp.decode("utf-8"))


def work_mode_off(ser: serial) -> bool:
    try:
        if sp.serial_transmit(ser, "WORK_MOD_OFF") != sp.SERIAL_OK:
            return True
        if sp.serial_receive(ser) != sp.SERIAL_OK:
            return True

    except Exception as e:
        print("Connection error: ", e.__class__)
        return True

    return False


def work_mode_on(ser: serial) -> bool:
    try:
        if sp.serial_transmit(ser, "WORK_MOD_ON") != sp.SERIAL_OK:
            return True
        if sp.serial_receive(ser) != sp.SERIAL_OK:
            return True

    except Exception as e:
        print("Connection error: ", e.__class__)
        return True

    return False


def change_interval(ser: serial, interval: int) -> bool:
    try:
        if interval < 1:
            return True
        if sp.serial_transmit(ser, "CHANGE_INT" + str(interval)) != sp.SERIAL_OK:
            return True
        if sp.serial_receive(ser) != sp.SERIAL_OK:
            return True
    except Exception as e:
        print("Connection error: ", e.__class__)
        return True

    return False


if __name__ == "__main__":
    ser = sp.open_serial()
    result = receive_all_measurements(ser)
    if result is None:
        print("No data or error during transmission")
    else:
        for m in result:
            print(m)

    print(get_time(ser))
    print(set_time(ser, 1653769495))
    print(get_time(ser))
