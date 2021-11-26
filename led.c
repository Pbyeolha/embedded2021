#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"

static int fd = 0;
static unsigned int ledValue = 0;

int ledLibInit(void)
{
   fd = open(LED_DRIVER_NAME, O_RDWR);
   ledValue = 0;

   if(fd < 0)
   {
      printf("led driver open error.\n");
      return 0;
   }

   return 1;
}
int ledOnOff(int ledNum, int onOff)
{
   int i=1;
   i = i <<ledNum;
   ledValue = ledValue & (~i);
   if (onOff != 0)
      ledValue |= i;
   write(fd, &ledValue, 4);
   
}

int ledStatus(void){}

int ledLibExit(void)
{
   ledValue=0;
   ledOnOff(0,0);
   close(fd);
}
