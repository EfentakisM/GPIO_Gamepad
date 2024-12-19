#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>
#include <signal.h>
#include <stdbool.h>
#include <linux/input.h>
#include "Gamepad.h"
#include <string.h>

struct uinput_user_dev uinp ;
 
int uinp_fd;






int create_gamepad(struct uinput_user_dev uinp,int uinp_fd)
{
   
    
   
    memset(&uinp, 0, sizeof(uinp));



    memcpy(uinp.name, "Custom Gamepad Name", 80);
    uinp.id.bustype = BUS_USB;
    
    uinp.id.vendor = 0x079; 
    uinp.id.product = 0x078;
    uinp.id.version = 0x0100; 

    static int abs[] = { ABS_X, ABS_Y, ABS_RX, ABS_RY};
    static int key[] = { BTN_A, BTN_B, BTN_Y, BTN_X, BTN_SELECT, BTN_MODE, BTN_START, BTN_TL, BTN_TR, BTN_THUMBL, BTN_THUMBR,-1};
    
    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
    for (int i = 0; i < 4; i++) {
        ioctl(uinp_fd, UI_SET_ABSBIT, abs[i]);
        uinp.absmin[abs[i]] = -32768;
        uinp.absmax[abs[i]] = 32768;
        uinp.absflat[abs[i]] = 1024;
    }
    
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    for (int i = 0; key[i] >= 0; i++) {
        ioctl(uinp_fd, UI_SET_KEYBIT, key[i]);
    }
    
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_DPAD_UP);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_DPAD_DOWN);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_DPAD_LEFT);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_DPAD_RIGHT);
    
    
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TL2);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_TR2);
    
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_GAMEPAD);
    ioctl(uinp_fd, UI_SET_PHYS, "stormpad/virtpad0");///////////////////////////////
    
   
    
    ioctl(uinp_fd, UI_SET_EVBIT, EV_SYN);
    ioctl(uinp_fd, UI_SET_KEYBIT, BTN_MODE);
    
    
    
    ssize_t res = write(uinp_fd, &uinp, sizeof(uinp));
    if (res < 0)
        perror("uinput device setup write");
    
    if(ioctl(uinp_fd, UI_DEV_CREATE)<0){
        perror("Failed to create uinput device");
        close(uinp_fd);
        return -1;
    }
    sleep(1);
    return 0;
}
int destroy_gamepad(){
    ioctl(uinp_fd, UI_DEV_DESTROY);
    close(uinp_fd);
    return 0;
}

int Initialize_Gamepad()
{
    uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(uinp_fd<0){
        return -1;
    }
    
    
    create_gamepad(uinp, uinp_fd);
   
    return 0;
}
int Send_Key_Event(struct input_event ev){
    
    write(uinp_fd, &ev, sizeof(ev));

    return 0;
}
int Refresh(){
    struct input_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;
    write(uinp_fd, &ev, sizeof(ev));
    return 0;
}
