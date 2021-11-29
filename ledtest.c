#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"
#define LED_DRIVER_NAME "/dev/periled"

static unsigned int ledValue=0;
static int fd = 0;

int main(int argc, char **argv){
    /*led*/
    unsigned int data = strtol(argv[1], NULL, 16);

    ledLibInit();
    for(int i=0;i<8;i++)
    {
        if(i==0) ledOnOff(0,1);
        else if(i==1) ledOnOff(1,1);
        else if(i==2)   ledOnOff(2,1);
        else if(i==3)   ledOnOff(3,1);
        else if(i==4)   ledOnOff(4,1);
        else if(i==5) ledOnOff(5,1);
        else if(i==6)  ledOnOff(6,1);
        else if(i==7)  ledOnOff(7,1);
    }
    //ledOnOff(data);
    ledStatus();
    sleep(10);
    ledLibExit();
    return 0;
}

