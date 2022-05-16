from flask import Flask, request, render_template, redirect, url_for
import time
import serial_port

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
        if len(zmienna)>0:
            if zmienna[0] =='t':
                return render_template('index.html',printTime=1,time=100)
            elif zmienna[0] =='d':
                try:
                    convDate=int(zmienna[1:len(zmienna)])
                    if convDate>2147483647:
                        return render_template('index.html',error=1,errorMess="Max value is 2147483647")
                    date2=time.ctime(convDate)
                    return render_template("index.html",a=1,date=date2)
                except:
                    return render_template('index.html',error=1,errorMess="Date command - d<value>")
            else:
                return render_template('index.html',error=1,errorMess="Wrong command")
        else:
            return render_template('index.html',error=1,errorMess="Write a command")
    else:
        return render_template('index.html')

@app.route("/revdata")
def recivedData():

  return render_template('recivedData.html')
# return "<p>Hello, World!</p>"
# return "<p>Hello, World!</p>"

