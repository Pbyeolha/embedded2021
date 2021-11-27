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

static unsigned int ledValue=0;
static int fd = 0;

int main(int argc, char **argv){
    /*led*/
    ledLibInit();
    for(int i=0;i<8;i++)
    {
        if(i==0) ledOnOff(1,1);
        else if(i=1) ledOnOff(2,1);
        else if(i=2)   ledOnOff(3,1);
        else if(i=3)   ledOnOff(4,1);
        else if(i=4)   ledOnOff(5,1);
        else if(i=5) ledOnOff(6,1);
        else if(i=6)  ledOnOff(7,1);
        else  ledOnOff(0,0);
    }
    ledLibExit();
    return 0;
}

