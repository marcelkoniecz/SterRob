from flask import Flask, request, render_template, redirect, url_for
import time
import serial_port as sp
from datetime import datetime

ser = sp.open_serial(sp.get_stm_port())
print(ser)
# port = "/dev/ttyACM1"
# ser=serial.Serial(port,115200)
# while True:
#    data=ser.readline()
#    data_sensor=data.decode('utf8')
#    print("aa" + data_sensor)

app = Flask(__name__)


# @app.route("/")
# def home()

@app.route("/", methods=["POST", "GET"])
def glowna():
    if request.method == "POST":
        zmienna = request.form["wartosc"]
        if len(zmienna) > 0:
            if zmienna[0] == 't':

                if sp.serial_transmit(ser, "GET_TIME") != sp.SERIAL_OK:
                    return render_template('index.html', error=1, errorMess="Command parse error!")
                data = sp.serial_receive(ser)
                if len(data) == 0:
                    return render_template('index.html', error=1, errorMess="No data received!")
                timestamp = int(data.decode("utf-8"))
                print(timestamp)
                date_time = datetime.fromtimestamp(timestamp)
                return render_template('index.html', printTime=1, time=date_time.strftime("%d/%m/%Y, %H:%M:%S"))
            elif zmienna[0] == 'd':
                try:
                    timestamp = int(zmienna[1:len(zmienna)])
                    if timestamp > 2147483647:
                        return render_template('index.html',error=1,errorMess="Max value is 2147483647")

                    mess = "SET_TIME" + str(timestamp)
                    if sp.serial_transmit(ser, mess) != sp.SERIAL_OK:
                        return render_template('index.html', error=1, errorMess="Command parse error!")

                    sa = sp.serial_receive(ser)
                    print(sa)
                    if sa == sp.SERIAL_OK:
                        date_time = datetime.fromtimestamp(timestamp)
                        res = "Date and time set to " + date_time.strftime("%d/%m/%Y, %H:%M:%S")
                        return render_template("index.html", a=1, date=res)

                    return render_template('index.html', error=1, errorMess="Can't set new timestamp")

                except:
                    return render_template('index.html', error=1, errorMess="Date command - d<value>")
            else:
                return render_template('index.html', error=1, errorMess="Wrong command")
        else:
            return render_template('index.html', error=1, errorMess="Write a command")
    else:
        return render_template('index.html')
####
#
#

@app.route("/revdata")
def recivedData():

  return render_template('recivedData.html')
# return "<p>Hello, World!</p>"
# return "<p>Hello, World!</p>"

