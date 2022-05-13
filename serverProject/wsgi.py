from flask import Flask, request, render_template, redirect, url_for
#import serial

#port = "/dev/ttyACM1"
#ser=serial.Serial(port,115200)
#while True:
#    data=ser.readline()
#    data_sensor=data.decode('utf8')
#    print("aa" + data_sensor)

app = Flask(__name__)

#@app.route("/")
#def home()

@app.route("/",methods=["POST","GET"])
def glowna():
    if request.method=="POST":
        #return render_template('index.html')
        zmienna=request.form["wrt"]
        #return "Wczytalem "+zmienna
        return render_template('index.html')
    else:
        return render_template('index.html')
   # return "<p>Hello, World!</p>"
# return "<p>Hello, World!</p>"   
   
    
