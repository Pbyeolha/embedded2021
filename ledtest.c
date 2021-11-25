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

int ledOnOff(int ledNum, int onOff){
    int i = 0; int j=0;
    // i = i<<ledNum;
    // ledValue = ledValue& (~i);
    // if (onOff !=0) ledValue |= i
    for(i=0; i<8; i++){ //bit 연산, led on
        ledOnOff(i, 1);
    }
    for(j=0; j<8; j++){
       ledOnOff(j, 0);
    }  
}

int ledLibInit(void){
    ledValue=0;
}

int ledLibExit(void){
    ledValue = 0;
}
