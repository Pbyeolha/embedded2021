#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"

static int fd = 0;
static unsigned int ledValue = 0;
static int bass, snare, hi_hat, tomtom, crash, ride, floor_tom=0; //드럼구성, global변수, 다른 app, lib에서도 사용 가능
int i=1;

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
   i = i <<ledNum;
   ledValue = ledValue & (~i);
   if (onOff != 0)
      ledValue |= i;
   write(fd, &ledValue, 4);
   
}

int ledStatus(void){
   if(i==1) printf("Bass Drum\n");
   else if(i==2) printf("Snare Drum\n");
   else if(i==3)   printf("Hi-Hat\n");
   else if(i==4)   printf("Tom Tom\n");
   else if(i==5)   printf("Floor Tom\n");
   else if(i==6) printf("Crash Cymbal\n");
   else if(i==7)  printf("Ride Cymbal\n");
}

int ledLibExit(void)
{
   ledValue=0;
   ledOnOff(0,0);
   close(fd);
}

