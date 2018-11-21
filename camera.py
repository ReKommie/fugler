from picamera import PiCamera
from time import sleep
from datetime import datetime
import serial

try:
    serial.Serial('/dev/ttyACM0',9600)
    ser = serial.Serial('/dev/ttyACM0',9600)  #klargjør for å lese av arduinoen sin serial, må sjekke mellom to porter 
except:                                       #fordi aruinoen kan være på en av dem, og det er tilfeldig hvilke
    serial.Serial('/dev/ttyACM1',9600)
    ser = serial.Serial('/dev/ttyACM1',9600) 
camera = PiCamera() #setter opp kamera
picture_nr = 0 #brukes for å lage filnavnet til bildet/videoen som blir tatt

def take_vid():
    camera.resolution = (640, 480)
    camera.annotate_text = 'Date: %s' % datetime.now() #legger til tekst med dato og tid
    camera.start_recording('/home/pi/Desktop/fugler/%s.h246' % str(picture_nr)) #bestemmer hvor filen skal lagres
    sleep(10)
    camera.stop_recording()

def take_pic():
    camera.capture('/home/pi/Desktop/fugler/%s.jpg' % str(picture_nr))

while True: #koden vil kjøre helt til noen avbryter
    read_serial = ser.readline()
    #print(read_serial)
    if 'Cheeeeeese' in str(read_serial): #dersom aruinoen sender 'cheese'(bevegelse er detekter) skal bilde bli tatt
        take_pic()
        #take_vid()
        picture_nr += 1
        
