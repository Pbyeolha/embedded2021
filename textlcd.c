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
#include "textlcddrv.h"

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

unsigned int linenum = 0;
stTextLCD  stlcd; 
int fd;
int len; 

int textLibInit(void){
    fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);

    if(fd < 0)
    {
      printf("textlcd driver open error.\n");
      return 0;
    }
    memset(&stlcd,0,sizeof(stTextLCD));
}

int lcdtextwrite(const char *str1, const char *str2, int lineFlag){
    linenum = strtol(str1, NULL, 10);
    printf("linenum: %d\n", linenum);
    if(linenum ==1) stlcd.cmdData=CMD_DATA_WRITE_LINE_1;
    else if(linenum==2) stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
    else{
        printf("linenum: %d wrong. range(1~2)\n", linenum);
        return 1;
    }

    len=strlen(str2);
    if(len>COLUMN_NUM) memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, COLUMN_NUM);
    else memcpy(stlcd.TextData[stlcd.cmdData - 1], str2, len);
    stlcd.cmd=CMD_WRITE_STRING;
    fd=open(TEXTLCD_DRIVER_NAME, O_RDWR);
    if(fd<0) {
        perror("driver (//dev//peritextlcd) open error.\n");
        return 1;
    }
    write(fd, &stlcd, sizeof(stTextLCD));


}

int textLibExit(void){
    close(fd);
}