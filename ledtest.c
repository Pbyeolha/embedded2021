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
#define LED_DRIVER_NAME      "/dev/periled"

int main(int argc, char** argv)
{
    
    ledLibInit();
    while(1){
        for (int i = 0; i < 8; i++)
        {
      
            ledOnOff(i, 1);
            ledStatus();
            sleep(1);
        }
        for (int i = 0; i < 8; i++)
        {
         
            ledOnOff(i, 0);
            ledStatus();
            sleep(1);
        }
    }
    sleep(10);
    ledLibExit();
    return 0;
}
