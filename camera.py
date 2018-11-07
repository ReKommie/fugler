from picamera import PiCamera
from time import sleep
from datetime import datetime
import serial

ser = serial.Serial('/dev/ttyACM0',9600) #klargjør for å lese av arduinoen sin serial
camera = PiCamera()
picture_nr = 0 #brukes for å lage filnavnet til bildet/videoen som blir tatt

while True:
    read_serial = ser.readline()
    print(read_serial)
    if '01' in str(read_serial): #dersom aruinoen sender '01'(bevegelse er detekter) skal bilde bli tatt
        camera.resolution = (640, 480)
        camera.annotate_text = 'Date: %s' % datetime.now()
        camera.start_recording('/home/pi/Desktop/fugler/%s.avi' % str(picture_nr))
        sleep(10)
        camera.stop_recording()
        #camera.capture('/home/pi/Desktop/fugler/%s.jpg' % str(picture_nr))
        picture_nr += 1
        