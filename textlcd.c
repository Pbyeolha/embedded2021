#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "textlcd.h"

#define TEXTLCD_DRIVER_NAME "/dev/peritextlcd"

stTextLCD stlcd;
int fd; int len;

int textlcdLibInit(void){
    fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);
    if(fd<0){
        perror("driver (//dev//peritextlcd) open error/\n");
        return 1;
    }
    memset(&stlcd, 0, sizeof(stTextLCD));
}

int lcdtextwrite(char *str1, char *str2){
    unsigned int linenum = 0;
    linenum = strtol(str1,NULL,10); 
    printf("linenum :%d\n", linenum); 
    if ( linenum == 1) stlcd.cmdData = CMD_DATA_WRITE_LINE_1; 
    else if ( linenum == 2) stlcd.cmdData = CMD_DATA_WRITE_LINE_2; 
    else { printf("linenum : %d wrong . range (1 ~ 2)\n", linenum); return 1; }
    len = strlen(str2); 
    if ( len > COLUMN_NUM) memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, COLUMN_NUM);
    else memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, len);
    stlcd.cmd = CMD_WRITE_STRING; fd = open(TEXTLCD_DRIVER_NAME,O_RDWR); // open driver
    if ( fd < 0 )
    {  perror("driver (//dev//peritextlcd) open error.\n"); 
        return 1; 
    }                    
    write(fd,&stlcd,sizeof(stTextLCD)); 
    
}
int textlcdexit(void)
{
	close(fd);
   return 0;
}