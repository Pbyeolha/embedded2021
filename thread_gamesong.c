#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/kd.h> //touchscreen
#include <sys/ioctl.h> //touchscreen

static pthread_t playsong_id[0];

static void* playsongFunc();

void gamesong()
{
    while(1)
    {
    pthread_create(&playsong_id[0], NULL, &playsongFunc, NULL);
    pthread_detach(playsong_id[0]);
    }
}

static void* playsongFunc()
{
    system("aplay gamesong.wav");
}

