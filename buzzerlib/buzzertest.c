#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"
#define MAX_SCALE_STEP 8

int main(int argc, char **argv)
{
    if(buzzerInit()==0)
    {
        printf("error\n");
        return 0;
    }
    
    for(int i=0; i<10; i++)
    {
        buzzerPlaySong(0);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(1);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(2);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(3);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(4);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(5);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(6);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(7);
        sleep(2);
        buzzerStopSong();

        buzzerPlaySong(8);
        sleep(2);
        buzzerStopSong();
    }
}