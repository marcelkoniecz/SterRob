from flask import Flask, request, render_template, redirect, url_for
import time
from datetime import datetime

from flask_bootstrap import Bootstrap
from flask_datepicker import datepicker

import serial_port as sp
import measurements_operations as mo
import database_operations as do
import serial_communication as sc

ser = [sp.open_serial()]
page = [10, 0]
print(ser[0])

app = Flask(__name__)
Bootstrap(app)
datepicker(app)


# @app.route("/home", methods=["POST", "GET"])
# def glowna():
#     if request.method == "POST":
#         zmienna = request.form["wartosc"]
#         if len(zmienna) > 0:
#             if zmienna[0] == 't':

#                 if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
#                     return render_template('index.html', error=1, errorMess="Command parse error!")
#                 data = sp.serial_receive(ser)
#                 if len(data) == 0:
#                     return render_template('index.html', error=1, errorMess="No data received!")
#                 timestamp = int(data.decode("utf-8"))
#                 print(timestamp)
#                 date_time = datetime.fromtimestamp(timestamp)
#                 return render_template('index.html', printTime=1, time=date_time.strftime("%d/%m/%Y, %H:%M:%S"))
#             elif zmienna[0] == 'd':
#                 try:
#                     timestamp = int(zmienna[1:len(zmienna)])
#                     if timestamp > 2147483647:
#                         return render_template('index.html',error=1,errorMess="Max value is 2147483647")

#                     mess = "SET_TIME" + str(timestamp)
#                     if sp.serial_transmit(ser, mess) != sp.SERIAL_OK:
#                         return render_template('index.html', error=1, errorMess="Command parse error!")

#                     sa = sp.serial_receive(ser)
#                     print(sa)
#                     if sa == sp.SERIAL_OK:
#                         date_time = datetime.fromtimestamp(timestamp)
#                         res = "Date and time set to " + date_time.strftime("%d/%m/%Y, %H:%M:%S")
#                         return render_template("index.html", a=1, date=res)

#                     return render_template('index.html', error=1, errorMess="Can't set new timestamp")

#                 except:
#                     return render_template('index.html', error=1, errorMess="Date command - d<value>")
#             else:
#                 return render_template('index.html', error=1, errorMess="Wrong command")
#         else:
#             return render_template('index.html', error=1, errorMess="Write a command")
#     else:
#         return render_template('index.html')


@app.route("/", methods=["POST", "GET"])
def home_page():
    do.create_database()

    if request.method == "POST":
        if request.form['submit_button'] == 'Pobierz':
            print("Pobieranie danych")
            meas = sc.receive_all_measurements(ser[0])
            print("Pobrano z urz??dzenia")
            if meas is not None:
                print("Dodawanie do bazy")
                for m in meas:
                    mo.insert_measurement(m)

        elif request.form['submit_button'] == 'Wyczy????':
            print("Czyszczenie bazy danych")
            do.clear_database("measurements")
            do.clear_database("measurements_sensors_data")

        elif request.form['submit_button'] == '<':
            print("Przesun baze w prawo")
            if page[1] > 0:
                page[1] -= page[0]
        elif request.form['submit_button'] == '>':
            print("Przesun baze w lewo")
            print(do.count_databases_rows("measurements"))
            print(page[1])
            print(page[0])
            if do.count_databases_rows("measurements") >= page[1] + page[0]:
                page[1] += page[0]


    list_of_meas = mo.get_measurements(page[0], page[1])
    tm_list = []

    if list_of_meas is None:
        print("EMPTY")
        list_of_meas = []
    else:
        mo.print_measurements(list_of_meas)
        for i in list_of_meas:
            temp_values = []
            for j in i.values:
                temp_values.append(int(j/40.95))
            tm_list.append((datetime.fromtimestamp(i.timestamp).strftime("%d/%m/%Y, %H:%M:%S"), temp_values))

    return render_template('homepage.html', my_list=list_of_meas, tm_list=tm_list, length=len(list_of_meas))
    # return render_template('homepage.html')


@app.route("/konfiguracja", methods=["POST", "GET"])
def konfig_page():
    if request.method == "POST":
        print(request.form['submit_button'])

        if (request.form['submit_button'] == 'Ustaw wybrany czas'):
            zmienna = request.form["czas"]
            zmienna2 = request.form["kalendarz"]
            if len(zmienna2) < 3:
                mes = "Aby poprawnie ustawi?? czas nale??y ustawi?? dat??"
            else:
                ts = int((datetime(int(zmienna2[6:10]), int(zmienna2[0:2]), int(zmienna2[3:5]),
                                   int(zmienna[0:2]), int(zmienna[3:5])) - datetime(1970, 1,
                                                                                    1)).total_seconds()) - 2 * 3600

                if sc.set_time(ser[0], ts) is True:
                    mes = "B????d komunikacji, nie mo??na ustawi?? daty i czasu"
                else:
                    date_time = datetime.fromtimestamp(ts)
                    message = date_time.strftime("%d/%m/%Y, %H:%M:%S")
                    mes = "Ustawiono nast??puj??cy?? dat?? i czas: " + str(message)

            return render_template('config.html', message=mes)

        elif (request.form['submit_button'] == 'Odczytaj aktualny czas'):
            ts = sc.get_time(ser[0])
            if ts is not None:
                date_time = datetime.fromtimestamp(ts)
                message = date_time.strftime("%d/%m/%Y, %H:%M:%S")
                mes = "Obecna data i czas urz??dzenia: " + str(message)
            else:
                mes = "B????d odczytu danych z urz??dzenia"
            return render_template('config.html', message=mes)

        elif (request.form['submit_button'] == 'Wzn??w prace loggera'):
            if sc.work_mode_on(ser[0]) is True:
                mes = "B????d wysy??ania polecenia do urz??dzenia"
            else:
                mes = "Praca loggera zosta??a wznowiona"
            return render_template('config.html', message=mes)

        elif (request.form['submit_button'] == 'Zatrzymaj logger'):
            if sc.work_mode_off(ser[0]) is True:
                mes = "B????d wysy??ania polecenia do urz??dzenia"
            else:
                mes = "Logger danych zosta?? zatrzymany"
            return render_template('config.html', message=mes)

        elif (request.form['submit_button'] == 'Zmie?? interwa?? mi??dzy pomiarami'):
            int_val = request.form['int_val']
            if sc.change_interval(ser[0], int(int_val)) is True:
                mes = "B????d wysy??ania polecenia do urz??dzenia"
            else:
                mes = "Logger danych wykonuje teraz pomiary co " + str(int_val) + " sekund"
            return render_template('config.html', message=mes)

        elif (request.form['submit_button'] == 'Po????cz z urz??dzeniem'):
            print("Przed:")
            print(ser[0])
            if sp.is_port_open(ser[0]):
                ser[0].close()
                ser[0] = None
            ser[0] = sp.open_serial()
            if sp.is_port_open(ser[0]):
                mes = "Port zosta?? poprawnie otwarty"
            else:
                mes = "B????d otwierania portu szeregowego lub nie znaleziono urz??dzenia"
            print("Po:")
            print(ser[0])

            #if sp.is_port_open(ser[0]):
            #    mes = "Port jest obecnie otwarty"
            # else:
            #    print(ser[0])
            #    ser[0] = sp.open_serial()
            #    print(ser[0])
            #    if sp.is_port_open(ser[0]):
            #        mes = "Port zosta?? poprawnie otwarty"
            #    else:
            #        mes = "B????d otwierania portu szeregowego lub nie znaleziono urz??dzenia"
            return render_template('config.html', message=mes)

    return render_template('config.html')

