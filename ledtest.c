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
    int i=0; int j=0;
    ledLibInit();

    for(i=0; i<8; i++){
        ledOnOff(i, 1); //led on
        ledStatus();
    }
    for(j=0; j<8; j++){ //led off
        ledOnOff(j, 0);
        ledStatus();
    }

    ledLibExit();
    return 0;
}

