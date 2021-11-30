#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
// first read input device
#define  INPUT_DEVICE_LIST	"/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

// int buttonInit(void)
// {
// if (probeButtonPath(buttonPath) == 0)
// return 0;
// fd=open (buttonPath, O_RDONLY);
// msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
// pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);
// return 1;
// }

int main(int argc, char *argv[]){
    int msgID = buttonLibInit();
    int returnValue = 0; 
    BUTTON_MSG_T messageRx;

    returnValue=msgrcv(msgID, &messageRx, sizeof(messageRx.messageNum), 0 , 0);
	
		if(returnValue<0)
			printf("Key input fail\n");
		switch(messageRx.keyInput)
			{
				case KEY_VOLUMEUP:	printf("Volume up key):");	break;
				case KEY_HOME:		printf("Home key):");		break;
				case KEY_SEARCH:	printf("Search key):");		break;
				case KEY_BACK:		printf("Back key):");		break;
				case KEY_MENU:		printf("Menu key):");		break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
			printf("\n");
	
	buttonLibExit();
    return 0;		
}
