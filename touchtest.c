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
#include "touch.h"

int main(int argc, char *argv[]){
    int x, y = 0; 
    int msgID = touchLibInit();
    int returnValue = 0; 

    TOUCH_MSG_T messageRx;
    
    while(1){
        returnValue=msgrcv(msgID, &messageRx, sizeof(messageRx.messageNum), 0 , 0);
        if(messageRx.messageNum == 1) //x좌표 
            printf("x: %d \n", messageRx.touchX);
        else if(messageRx.messageNum == 2) //y좌표
            printf("y: %d \n", messageRx.touchY);

        usleep(10000);
    }

    touchLibExit();

    return 0;
}