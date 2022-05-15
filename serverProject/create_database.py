import sqlite3
import os


def create_database():
    if os.path.isfile("database/sensors_data.db"):
        print("Database already exists!")
        return True
    else:
        try:
            con = sqlite3.connect('file:database/sensors_data.db?mode=rwc', uri=True)
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

            con.commit()
            con.close()

            print("Database created successfully!")
            return False
        except Exception as e:
            template = "An exception of type {0} occurred. Arguments:\n{1!r}"
            message = template.format(type(e).__name__, e.args)
            print(message)
            return True


if __name__ == "__main__":
    create_database()
