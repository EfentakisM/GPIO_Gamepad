#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/input.h>


int create_gamepad(struct uinput_user_dev uinp,int uinp_fd);
int destroy_gamepad();
int Initialize_Gamepad();
int Send_Key_Event(struct input_event ev);
int Refresh();

#endif