import RPi.GPIO as GPIO
import time


GPIO.setmode(GPIO.BCM)

GPIO.setup(21,GPIO.IN, pull_up_down=GPIO.PUD_UP)

while True:
    input = GPIO.input(21)
    if (input ==False):
        print("Button Pressed")
        time.sleep(0.2)