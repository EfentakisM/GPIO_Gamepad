#include <stdio.h>
#include "Gamepad.h"
#include <linux/uinput.h>
#include <linux/input.h>
#include <string.h>
#include <time.h>
#include <errno.h>


int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}



int main(){
    printf("%s","Sex"); 
    
    Initialize_Gamepad();
    
    
    msleep(2000);
    struct input_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.type = EV_KEY;
    ev.code = BTN_A;
    ev.value = 1;
    
    Send_Key_Event(ev);
    Refresh();
    msleep(1000);
    destroy_gamepad();

}