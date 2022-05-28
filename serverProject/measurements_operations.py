import database_operations as db
from typing import NamedTuple
import sqlite3
import os


class Measurement(NamedTuple):
    timestamp: int
    values: list


def insert_measurement(m: Measurement):
    con = db.connect_database()
    cur = con.cursor()
    cur.execute("SELECT id FROM measurements ORDER BY id DESC")
    rows = cur.fetchone()
    if rows is None:
        last_id = 0
    else:
        last_id = sum(rows) + 1

    sql = ''' INSERT INTO measurements(id, time) VALUES(?, ?) '''
    cur.execute(sql, (last_id, m.timestamp,))

    for i in range(len(m.values)):
        cur.execute('''
            INSERT INTO measurements_sensors_data(id_measurement, id_sensor,  value) 
            VALUES (?, ?, ?)''', (last_id, i, m.values[i]))

    con.commit()
    con.close()


def get_measurements(limit=100, offset=0):
    meas_list = []
    con = db.connect_database()
    cur = con.cursor()

    cur.execute("SELECT COUNT(*) FROM measurements")
    rows = cur.fetchone()
    if rows is None:
        return None
    else:
        num_rows = sum(rows)
    if offset >= 0 and limit > 0:
        if offset > num_rows:
            return None
        elif (offset + limit) > num_rows:
            limit = num_rows - offset
    sql = "SELECT id, time FROM measurements ORDER BY id LIMIT " + str(limit) + " OFFSET " + str(offset)
    rows = cur.execute(sql).fetchall()

    for row in rows:
        sql = "SELECT value FROM measurements_sensors_data WHERE id_measurement = " + str(row[0]) + " ORDER BY id_sensor"
        val_list = []
        for v in cur.execute(sql).fetchall():
            val_list.append(v[0])
        meas_list.append(Measurement(row[1], val_list))

    return meas_list


def print_measurements(meas_list: list):
    for m in meas_list:
        print(m)


if __name__ == "__main__":
    db.create_database()

    m = Measurement(165000000, list(range(1, 10)))

    # db.clear_database("measurements")
    # db.clear_database("measurements_sensors_data")

    print("BEFORE\n")
    print("measurements")
    # db.print_database("measurements")
    list_of_meas = get_measurements()
    if list_of_meas is None:
        print("EMPTY")
    else:
        print_measurements(list_of_meas)
    # print("measurements_sensors_data")
    # db.print_database("measurements_sensors_data")

    insert_measurement(m)

    print("AFTER\n")
    print("measurements")
    list_of_meas = get_measurements()
    if list_of_meas is None:
        print("EMPTY")
    else:
        print_measurements(list_of_meas)
    # db.print_database("measurements")
    # print("measurements_sensors_data")
    # db.print_database("measurements_sensors_data")

