#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <pthread.h>
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl

#include "led.h"
#include "button.h"
#include "textlcd.h"
#include "buzzer.h"
#include "fnd.h"
#include "touch.h"
#include "bitmap.h"

static int msgID_button = 0;
static int msgID_touch = 0;
int returnvalue_button = 0;
int returnvalue_touch = 0;
int stage1, stage2, stage3, stage4 = 0;
int start = 0;
int x, y = 0; 
char filename[200] = {0,};
BUTTON_MSG_T messageRx_b;
TOUCH_MSG_T messageRx_t;

int main(int argc, char *argv[]){
    //=============init=============//
    ledLibInit();
    msgID_button = buttonLibInit();
    textlcdLibInit();
    buzzerLibInit();
    fndLibInit();
    msgID_touch = touchLibInit();

    lcdtextwirte("To start:", "Press 1");

    //=============Game start=============//
    whie(1){
        returnvalue_button = msgrcv(msgID_button, &messageRx_b, sizeof(messageRx.messageNum), 0 , 0);
        if(returnvalue_button <0 ) printf("key input fail!\n");
        switch(messageRx_b.keyInput){
			case KEY_VOLUMEUP:	printf("Game start:");	start = 1; break;
			case KEY_HOME:		printf("1st stage:"); start = 1; stage1 = 1;	break;
			case KEY_SEARCH:	printf("Search key):");	start = 1; stage2 = 1; break;
			case KEY_BACK:		printf("Back key):"); start = 1 ; stage3 = 1;	break;
			case KEY_MENU:		printf("Menu key):"); start = 1; stage4 = 1; break;
			case KEY_VOLUMEDOWN:printf("Volume down key):"); start = 0; break;
        }

        if(start==1 && stage1 ==1){ //stage1
            buzzerPlaySong(0);
            sleep(1);
            buzzerStopSong();
            for(int i = 0; i<8; i++){
                ledOnOff(i, 1);
                ledStatus();
                sleep(1);
            }
            for(int j = 0; j<8; j++){
                ledOnOff(j, 0);
                ledStatus();
                sleep(1);
            }
            fndDisp(2, 0); //그림 2개 맞춰야 함
            show_bmp("./flower.bmp");
            returnvalue_touch = msgrcv(msgID_touch, &messageRx_t, sizeof(messageRx_t.messageNum), 0, 0);
            if(messageRx.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx.touchX);
            else if(messageRx.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx.touchY);

        }
    }

    //=============exit=============//
    ledLibExit();
    buttonLibExit();
    textlcdLibExit();
    buzzerLibExit();
    fndLibExit();
    touchLibExit();

    return 0;
}