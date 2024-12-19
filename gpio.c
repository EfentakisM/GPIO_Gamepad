#include <pigpio.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include "Gamepad.h"
#include <string.h>
#define PRESSED 1
#define RELEASED -1
#define MAX_THREADS 2

struct key{
    char name[10];
    int gpio;
    int index;
    int keycode;
}typedef key;

key keys[16];

void buttons_setup();



int button_released(key key);
int button_pressed(key key);

int prev_state[] = {1,1,1,1,1,1};

int buttons[]={7,8,12,16,20,21};


void make_threads();
int initialize_buttons();
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



void *thread_function(void *arg) {
    
    key *keyT = (key *)arg;
    int gpioT = keyT->gpio;
    int indexT = keyT->index;
    while(gpioRead(gpioT)==0){
        msleep(10);
    }
    button_released(*keyT);
    return NULL;
}
int main(void)
{

    if (gpioInitialise() < 0)
    {
        printf("%s","pigpio initialisation failed.");
        return 1;
    }
    buttons_setup();
    initialize_buttons();
    
    Initialize_Gamepad();
    printf("%s","Test starting\n");
    
    
    
    while(1){
        
        

        for(int i = 0;i<6;i++){ 
            if(prev_state[i]!=gpioRead(keys[i].gpio) ){ 
                    
                if(gpioRead(keys[i].gpio)==0)
                    button_pressed(keys[i]);
                else
                    button_released(keys[i]);
                }
            
                
            Refresh();
            msleep(10);    }
        
    }
    
    return 1;
}

int initialize_buttons(){

    for(int i=0;i<6;i++){
        
        gpioSetMode(keys[i].gpio, PI_INPUT);
        printf("%d\n",keys[i].gpio);
        gpioSetPullUpDown(keys[i].gpio, PI_PUD_UP);
    }
    
    
    

    return 1;
}

int button_pressed(key key){
    struct input_event ev_p;
    memset(&ev_p, 0, sizeof(ev_p));
    ev_p.type = EV_KEY;
    ev_p.code = key.keycode;
    ev_p.value = 1;
    Send_Key_Event(ev_p);
    prev_state[key.index] = 0;
    
    return 0;
}

int button_released(key key){
   struct input_event ev_r;
    memset(&ev_r, 0, sizeof(ev_r));
    ev_r.type = EV_KEY;
    ev_r.code = key.keycode;
    ev_r.value = 0;
    Send_Key_Event(ev_r);
    prev_state[key.index] = 1;
    return 0;
}

void buttons_setup(){

    key key1,key2,key3,key4,key5,key6;
    key1.index = 0;
    key1.gpio = 7;
    key1.keycode = BTN_X;
    
    key2.index = 1;
    key2.gpio = 8;
    key2.keycode = BTN_A;
    
    key3.index = 2;
    key3.gpio = 12;
    key3.keycode = BTN_Y;
    
    key4.index = 3;
    key4.gpio = 16;
    key4.keycode = BTN_B;

    key5.index = 4;
    key5.gpio = 20;
    key5.keycode = BTN_TR;
    
    key6.index = 5;
    key6.gpio = 21;
    key6.keycode = BTN_TL;
    
    keys[0]=key1;
    keys[1]=key2;
    keys[2]=key3;
    keys[3]=key4;
    keys[4]=key5;
    keys[5]=key6;
    
}
