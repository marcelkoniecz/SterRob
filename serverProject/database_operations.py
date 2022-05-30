import sqlite3
import os


DATABASE_PATH = "database/sensors_data.db"

SENSORS_LIST = [
    (1, "Sensor [0,0]"),
    (2, "Sensor [0,1]"),
    (3, "Sensor [0,2]"),
    (4, "Sensor [1,0]"),
    (5, "Sensor [1,1]"),
    (6, "Sensor [1,2]"),
    (7, "Sensor [2,0]"),
    (8, "Sensor [2,1]"),
    (9, "Sensor [2,2]"),
]


def connect_database():
    try:
        return sqlite3.connect('file:' + DATABASE_PATH + '?mode=rwc', uri=True)
    except Exception as e:
        template = "An exception of type {0} occurred. Arguments:\n{1!r}"
        message = template.format(type(e).__name__, e.args)
        print(message)
        raise


def create_database():
    if os.path.isfile(DATABASE_PATH):
        print("Database already exists!")
        return True
    else:
        try:
            if not os.path.isdir("database"):
                os.mkdir("database")
            con = connect_database()
            cur = con.cursor()

            # Create tables
            cur.execute('''CREATE TABLE measurements(
            id          INTEGER     PRIMARY KEY AUTOINCREMENT,
            time        INT         NOT NULL
            )''')

            cur.execute('''CREATE TABLE sensors(
            id          INTEGER     PRIMARY KEY AUTOINCREMENT,
            description TEXT        NOT NULL
            )''')

            cur.execute('''CREATE TABLE measurements_sensors_data(
            id_measurement      INTEGER,
            id_sensor           INTEGER,
            value               INTEGER,
            FOREIGN KEY(id_measurement) REFERENCES measurements(id),
            FOREIGN KEY(id_sensor)      REFERENCES sensors(id)
            )''')

            cur.executemany('''INSERT INTO sensors(id, description) VALUES (?, ?)''', SENSORS_LIST)

            con.commit()
            con.close()

            print("Database created successfully!")
            return False
        except Exception as e:
            template = "An exception of type {0} occurred. Arguments:\n{1!r}"
            message = template.format(type(e).__name__, e.args)
            print(message)
            return True


def clear_database(name: str):
    con = connect_database()
    cur = con.cursor()
    sql = "delete from " + name
    cur.execute(sql)
    con.commit()
    con.close()


def count_databases_rows(name: str) -> int:
    con = connect_database()
    cur = con.cursor()
    sql = "SELECT COUNT(*) FROM " + name
    cur.execute(sql)

    num = 0
    rows = cur.fetchone()
    if rows is not None:
        num = sum(rows)

    con.close()
    return num

def print_database(name: str):
    con = connect_database()
    cur = con.cursor()
    sql = "SELECT * FROM " + name
    cur.execute(sql)
    response = cur.fetchall()

    if len(response) == 0:
        print("Empty")
    else:
        for row in response:
            print(row)

    con.close()


if __name__ == "__main__":
    create_database()
