import serial
from flask import Flask
app = Flask(__name__)

@app.route('/')
def index():
    
    
    
if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
    s = serial.Serial('COM6', 115200)
    x = ""
    for i in range(1, 10):
        x+=(s.readline())

    
