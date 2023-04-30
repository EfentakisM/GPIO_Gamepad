gcc -c Gamepad.c
ar rcs libGamepad.a Gamepad.o
rm ./libs/libGamepad.a
mv ./libGamepad.a ./libs/libGamepad.a
echo done