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

#define  INPUT_DEVICE_LIST	"/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int msgID_button = 0;
int msgID_touch = 0;
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
    //msgID_button = buttonLibInit();
    textlcdLibInit();
    buzzerInit();
    //fndLibInit();
    //msgID_touch = touchLibInit();

    lcdtextwrite("1", "Press 1");

    //=============Game start=============//
    while(1){
    int msgID = buttonLibInit();
    int returnValue = 0; 
    BUTTON_MSG_T messageRx;

    returnValue=msgrcv(msgID, &messageRx, sizeof(messageRx.messageNum), 0 , 0);
   
      if(returnValue<0)
         printf("Key input fail\n");
      switch(messageRx.keyInput)
         {
            case KEY_VOLUMEUP:   printf("Volume up key):"); stage4=1;  break;
            case KEY_HOME:      printf("Home key):"); start=1;     break;
            case KEY_SEARCH:   printf("Search key):"); stage2=1;     break;
            case KEY_BACK:      printf("Back key):"); stage1=1;     break;
            case KEY_MENU:      printf("Menu key):"); stage3=1;     break;
            case KEY_VOLUMEDOWN:printf("Volume down key):");break;
         }
         printf("\n");

        if(stage1 ==1){ //stage1
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
            if(messageRx_t.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx_t.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx_t.touchY);

        }
        else if(stage2 ==1){ //stage1
            buzzerPlaySong(1);
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
            if(messageRx_t.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx_t.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx_t.touchY);

        }
        else if(stage3 ==1){ //stage1
            buzzerPlaySong(2);
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
            if(messageRx_t.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx_t.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx_t.touchY);

        }
        else if(stage4 ==1){ //stage1
            buzzerPlaySong(3);
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
            if(messageRx_t.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx_t.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx_t.touchY);

        }
        if(start ==1){ //stage1
            buzzerPlaySong(4);
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
            if(messageRx_t.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRx_t.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRx_t.touchY);

        }
    }

    //=============exit=============//
    ledLibExit();
    buttonLibExit();
    textlcdLibexit();
    buzzerExit();
    //fndLibExit();
    touchLibExit();

    return 0;
}