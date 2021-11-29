#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "led.h"

#define LED_DRIVER_NAME "/dev/periled"

static int fd = 0;
static unsigned int ledValue = 0;
static int bass, snare, hi_hat, tomtom, crash, ride, floor_tom=0; //드럼구성, global변수, 다른 app, lib에서도 사용 가능

int ledOnOff(int ledNum,int onOff)
{
   int i;
   i = i <<ledNum;
   ledValue = ledValue & (~i);
   if (onOff != 0)
    ledValue |= i;
   //ledValue=ledNum;
   write(fd, &ledValue, 4);
}

int ledLibInit(void)
{
   fd = open(LED_DRIVER_NAME, O_WRONLY);
   ledValue = 0;

   if(fd < 0)
   {
      printf("led driver open error.\n");
      return 0;
   }
   
   return 1;
}

int ledStatus(void){
   if(ledValue==0x01) printf("Bass Drum\n");
   else if(ledValue==0x02) printf("Snare Drum\n");
   else if(ledValue==0x03)   printf("Hi-Hat\n");
   else if(ledValue==0x04)   printf("Tom Tom\n");
   else if(ledValue==0x10)   printf("Floor Tom\n");
   else if(ledValue==0x20) printf("Crash Cymbal\n");
   else if(ledValue==0x30)  printf("Ride Cymbal\n");
}

int ledLibExit(void)
{
   // ledValue=0;
   // ledOnOff(0,0);
   close(fd);
}

