from flask import Flask, request, render_template, redirect, url_for
import time
import datetime

from flask_bootstrap import Bootstrap
from flask_datepicker import datepicker

#import serial_port as sp

import measurements_operations as mo
import database_operations as do

#ser = sp.open_serial(sp.get_stm_port())
#print(ser)
# port = "/dev/ttyACM1"
# ser=serial.Serial(port,115200)
# while True:
#    data=ser.readline()
#    data_sensor=data.decode('utf8')
#    print("aa" + data_sensor)

app = Flask(__name__)
Bootstrap(app)
datepicker(app)


# @app.route("/")
# def home()

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
    list_of_meas = mo.get_measurements(10)
    if list_of_meas is None:
        print("EMPTY")
    else:
        mo.print_measurements(list_of_meas)
    if request.method == "POST":
        if request.form['submit_button']== 'Pobierz':
            print("Pobieranie danych")
            list_of_meas = mo.get_measurements(10)
            if list_of_meas is None:
              print("EMPTY")
            else:
               mo.print_measurements(list_of_meas)

        elif request.form['submit_button']== 'Wyczyść':
            do.clear_database("measurements")
            do.clear_database("measurements_sensors_data")
            print("Czyszczenie bazy danych")
        elif request.form['submit_button']== 'Widok':
            print("Widok bazy danych")


    return render_template('homepage.html',my_list=list_of_meas)
    # return render_template('homepage.html')

# return "<p>Hello, World!</p>"
# return "<p>Hello, World!</p>"

@app.route("/konfiguracja", methods=["POST", "GET"])
def konfig_page():
    if request.method == "POST":

        if(request.form['submit_button']=='Ustaw wybrany czas'):
            zmienna = request.form["czas"]
            zmienna2=request.form["kalendarz"]
            if len(zmienna2)<3:
                mes="Aby poprawnie ustawić czas należy ustawić date"
            else:
               # mes="Ustawianie wybranego czasu: " + zmienna +" "+ zmienna2
                ts=(datetime.datetime(int(zmienna2[6:10]),int(zmienna2[0:2]),int(zmienna2[3:5]),int(zmienna[0:2]),int(zmienna[3:5]))-datetime.datetime(1970,1,1)).total_seconds()
                print(ts)
                mes="Ustawiono: "+ str(ts)
            return render_template('config.html',message=mes)

        elif(request.form['submit_button']=='Odczytaj aktualny czas'):
           # if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
           #     return render_template('config.html',message="Command parse error!")
           # data = sp.serial_receive(ser)
           # if len(data) == 0:
           #      return render_template('config.html',message="No data received!")
           # timestamp = int(data.decode("utf-8"))
           # print(timestamp)
           # date_time = datetime.fromtimestamp(timestamp)
           # return render_template('config.html',message=date_time.strftime("%d/%m/%Y, %H:%M:%S"))

            mes="Aktualny czas"
            print(mes)
            return render_template('config.html',message=mes)
            #alert( 'Hello, world!' );
        elif(request.form['submit_button']=='Wznów prace loggera'):
           # if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
           #     return render_template('config.html',message="Command parse error!")
            mes="Praca loggera została wznowiona"
            print(mes)
            return render_template('config.html',message=mes)
        elif(request.form['submit_button']=='Zatrzymaj logger'):
           # if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
           #     return render_template('config.html',message="Command parse error!")
            mes="Logger zastał zatrzymany"
            print(mes)
            return render_template('config.html',message=mes)
    #if request.method=="GET"
    return render_template('config.html')