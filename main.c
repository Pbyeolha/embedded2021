#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <pthread.h>
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl

#include "led.h"
#include "button.h"
#include "textlcd.h"
#include "buzzer.h"
#include "fnd.h"
#include "touch.h"
#include "bitmap.h"

#define  INPUT_DEVICE_LIST   "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int stage1, stage2, stage3, stage4 = 0;
int start = 0;
int x, y = 0; 
char filename[200] = {0,};

static void *thread_song()
{   
    if(buzzerInit()==0)
    {
        printf("error\n");
        return 0;
    }
    buzzerInit();
    sleep(1);
    while(1)
    {
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, 1);
            ledStatus();
            sleep(1);
        }
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, 0);
            ledStatus();
            sleep(1);
        }
    }
    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(0); //도
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(0); //도
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(2); //미
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(1); //레
    sleep(1);
    buzzerStopSong();

    buzzerPlaySong(0); //도
    sleep(1);
    buzzerStopSong();
    }
}

int main(int argc, char *argv[]){
    pthread_t thread[2];
    //=============song==============//
      pthread_create(&thread[0], NULL, &thread_song, NULL);
      pthread_join(thread_song,NULL);
    //=============init=============//
    ledLibInit();
    textlcdLibInit();
    buzzerInit();

    lcdtextwrite("1", "To Gamestart");
    lcdtextwrite("2", "press Home key");
    //=============Game start=============//
    while(1){
    int msgID = buttonLibInit();
    int msgIDt = touchLibInit();
    int returnValue = 0; 
    int returnValue1 = 1;
    BUTTON_MSG_T messageRx;

    returnValue=msgrcv(msgID, &messageRx, sizeof(messageRx.messageNum), 0 , 0);
   
      if(returnValue<0)
         printf("Key input fail\n");

      switch(messageRx.keyInput)
        {
            case KEY_VOLUMEUP:   printf("STAGE 4"); stage4=1;  break;
            case KEY_HOME:      printf("GAME START"); start=1;     break;
            case KEY_SEARCH:   printf("STAGE 2"); stage2=1;     break;
            case KEY_BACK:      printf("STAGE 1"); stage1=1;     break;
            case KEY_MENU:      printf("STAGE 3"); stage3=1;     break;
            case KEY_VOLUMEDOWN:printf("GAME FINISH");break;
        }
        printf("\n");
        if(start ==1){ //start
            lcdtextwrite("1", "hello!\n");
            lcdtextwrite("2", "Have a nice playing\n");
        }  

        if(stage1 ==1){ //stage1
            lcdtextwrite("1", "STAGE 1\n");
            show_bmp("stage1_menual.bmp");
            sleep(5);
            show_bmp("stage1_question.bmp");
            sleep(5);
            lcdtextwrite("2", "press button where is question's picture \n");
            show_bmp("stage1_1.bmp");
            fndDisp(1, 0);
            sleep(3);
            show_bmp("stage1_2.bmp");
            fndDisp(2, 0);
            sleep(3);
            show_bmp("stage1_3.bmp");
            fndDisp(3,0);
            sleep(3);
            
            if(stage2 == 1){ //두번째 button 눌렸을 때
                fndDisp(2, 0);
                show_bmp("stage_correct.bmp");
                lcdtextwrite("1", "Correct!\n");
                lcdtextwrite("2", "Go to Next stage!\n");
            }
            else if(stage1 == 1){ //첫번째 button 눌렸을 때
                fndDisp(1, 0);
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry\n");
                lcdtextwrite("2", "You're wrong\n")
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                fndDisp(3, 0);
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry\n");
                lcdtextwrite("2", "You're wrong\n");
            }
        }
        else if(stage2 ==1){ //stage2
            lcdtextwrite("1", "STAGE 2\n");
            show_bmp("stage2_menual.bmp");
            sleep(5);
            show_bmp("stage2_question.bmp");
            sleep(5);
            lcdtextwrite("2", "press button Who am I \n");
            show_bmp("stage2_1.bmp");
            fndDisp(1, 0);
            sleep(3);
            show_bmp("stage2_2.bmp");
            fndDisp(2, 0);
            sleep(3);
            show_bmp("stage2_3.bmp");
            fndDisp(3,0);
            sleep(3);
            
            if(stage1 == 1){ //첫번째 button 눌렸을 때
                fndDisp(1, 0);
                show_bmp("stage2_correct.bmp");
                lcdtextwrite("1", "Correct!\n");
                lcdtextwrite("2", "Go to Next stage!\n");
            }
            else if(stage2 == 1){ //두번째 button 눌렸을 때
                fndDisp(2, 0);
                show_bmp("stage2_uncorrect.bmp");
                lcdtextwrite("1", "Sorry\n");
                lcdtextwrite("2", "You're wrong\n")
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                fndDisp(3, 0);
                show_bmp("stage2_uncorrect.bmp");
                lcdtextwrite("1", "sorry\n");
                lcdtextwrite("2", "You're wrong\n");
            }
        }
        else if(stage3 ==1){ //stage3
 
                ledOnOff(6, 1);

            fndDisp(4, 0); //그림 4개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1 = msgrcv(msgIDt, &messageRxt, sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRxt.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
        else if(stage4 ==1){ //stage4

                ledOnOff(8, 1);

 
            fndDisp(5, 0); //그림 5개 맞춰야 함
            show_bmp("./flower.bmp");
            returnValue1 = msgrcv(msgIDt, &messageRxt, sizeof(messageRxt.messageNum), 0, 0);
            if(messageRxt.messageNum == 1) //x좌표 
                printf("x: %d \n", messageRxt.touchX);
            else if(messageRxt.messageNum == 2) //y좌표
                printf("y: %d \n", messageRxt.touchY);

        }
    }

    //=============exit=============//
    ledLibExit();
    buttonLibExit();
    textlcdLibexit();
    buzzerExit();
    touchLibExit();

    return 0;
}