#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/”
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"
char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static int fd_enable;
static int fd_freq;

const int musicScale[MAX_SCALE_STEP] =
{
    262, /* do */
    294, /* re */
    330, /* mi */
    349, /* fa */
    392, /* sol */
    440, /* ra */
    494, /* si */ 
    523 /* do */
};

int findBuzzerSysPath()
{
    DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL)
    {
        while(1)
        {
            struct dirent *dir_entry;   
            dir_entry = readdir (dir_info);
            if (dir_entry == NULL) break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
            {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
            }
        }
    }
    printf("find %s\n",gBuzzerBaseSysDir);
    return ifNotFound;
}
//버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것

void buzzerEnable(int bEnable)
{
    if(bEnable)
        write(fd_enable,&"1",1);
    else
        write(fd_enable,&"0",1);
}

void setFrequency(int frequency)
{
    dprintf(fd_freq,"%d",frequency);
}

int buzzerInit(void)
{
    if(findBuzzerSysPath()==0)
        return 0;
    printf("buzzer start...\n");
    char path[200];
    /*buzzerEnable*/
    sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
    int fd_enable=open(path,O_WRONLY);

    /*setFrequency*/
    sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
    int fd_freq=open(path,O_WRONLY);
}

int buzzerExit(void)
{
    printf("buzzer out..\n");
    buzzerEnable(0);
    close(fd_enable);
    close(fd_freq);
    return 0;
}

int buzzerPlaySong(int scale)
{
    setFrequency(musicScale[scale]);
    buzzerEnable(1);
    return 1;
}

int buzzerStopSong(void)
{
    buzzerEnable(0);
    return 0;
}
