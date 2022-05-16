import create_database as db
from typing import NamedTuple
import sqlite3
import os


class Measurement(NamedTuple):
    timestamp: int
    values: list


def insert_measurement(m: Measurement):
    con = db.connect_database()
    cur = con.cursor()
    sql = ''' INSERT INTO measurements(time) VALUES(?) '''
    cur.execute(sql, (m.timestamp,))
    cur.execute("SELECT last_insert_rowid()")

    rows = cur.fetchall()
    row = rows[0]

    cur.executemany('''
        INSERT INTO measurements_sensors_data(id_measurement, id_sensor,  value) 
        VALUES (?, ?, ?)''', (row, list(range(1, 9 + 1)), m.values))

    con.commit()
    con.close()


if __name__ == "__main__":
    db.create_database()
    m = Measurement(165000000, list(range(1, 10)))
    insert_measurement(m)
