#!/bin/sh
gcc -c Gamepad.c
ar rcs libGamepad.a Gamepad.o

gcc -o gamepad_exec gpio.c libGamepad.a -L/usr/lib -lpigpio
echo done
