#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"

static int fd = 0;
static int ledStatus = 0;

int ledLibInit(void)
{
   fd = open(LED_DRIVER_NAME, O_RDWR);
   ledStatus = 0;

   if(fd < 0)
   {
      printf("led driver open error.\n");
      return 0;
   }
   ledOffAll();
   return 1;
}
int ledOnOff(int ledNum, int onOff)
{
   int i=1;
   i = i <<ledNum;
   ledStatus = ledStatus & (~i);
   if (onOff != 0)
      ledStatus |= i;
   write(fd, &ledStatus, 4);
   
}

// int ledValue(void)
// {
//     //ledStatus = 0x00;
//    return ledStatus;
// }

int ledLibExit(void)
{
   ledOffAll();
   close(fd);
}
