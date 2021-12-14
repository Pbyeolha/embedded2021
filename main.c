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

int stage1, stage2, stage3, stage4 = 0;
int start = 0;
int x, y = 0; 
char filename[200] = {0,};

int main(int argc, char *argv[]){
    //=============init=============//
    ledLibInit();
    textlcdLibInit();
    buzzerInit();

    lcdtextwrite("1", "To Gamestart");
    lcdtextwrite("2", "press Home key")
    //=============Game start=============//
    while(1){
    int msgID = buttonLibInit();
    int msgIDt = touchLibInit();
    int returnValue = 0; 
    int returnValue = 1;
    BUTTON_MSG_T messageRx;
    TOUCH_MSG_T messageRxt;

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
        if(start ==1){ //start
            ledOnOff(8, 1);
            lcdtextwrite("1", "hello!\n");
            lcdtextwrite("2", "Have a nice playing\n");
        }  

        if(stage1 ==1){ //stage1
            ledOnOff(2, 1);

            fndDisp(2, 0); //그림 2개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1= msgrcv(msgIDt, &messageRxt sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRxt.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
        else if(stage2 ==1){ //stage2
            ledOnOff(4, 1);
            fndDisp(3, 0); //그림 3개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1 = msgrcv(msgIDt, &messageRxt, sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRx_t.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
        else if(stage3 ==1){ //stage3
 
                ledOnOff(6, 1);

            fndDisp(4, 0); //그림 4개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1 = msgrcv(msgIDt, &messageRxt, sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRxt.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
        else if(stage4 ==1){ //stage4

                ledOnOff(8, 1);

 
            fndDisp(5, 0); //그림 5개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1 = msgrcv(msgID_touch, &messageRxt, sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRxt.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
    }

    //=============exit=============//
    ledLibExit();
    buttonLibExit();
    textlcdLibexit();
    buzzerExit();
    touchLibExit();

    return 0;
}