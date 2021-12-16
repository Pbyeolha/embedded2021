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
#include "libbmp.h"
#include "bitmapFileHeader.h"
#include "touch.h"

static pthread_t button_ID;
static pthread_t led_ID;
static pthread_t touch_ID;
static pthread_t gameid[3];

static int msgID = 0;
static int msgIDt = 0;
int game1, game2, game3;
int rand1, rand2, rand3;
int start; int x, y;

void *thread_led();
void *thread_button();
void *thread_touch();
void *thread_start();
void *thread_game1();
void *thread_game2();
void *thread_game3();

int main(void){
    //=============Init=============//
    ledLibInit();
    buzzerInit();
    textlcdLibInit();
    msgID = buttonLibInit();
    msgIDt = TouchLibInit();

    //=============Init_Thread=============//
    pthread_create(&led_ID, NULL, &thread_led, NULL);
    pthread_create(&button_ID, NULL, &thread_button, NULL);
    pthread_create(&touch_ID, NULL, &thread_touch, NULL);

    pthread_join(led_ID, NULL);
    pthread_join(button_ID, NULL);
    pthread_join(touch_ID, NULL);
    //=============Exit=============//
    ledLibExit();
    buzzerExit();
    textlcdLibExit();
    TouchLibExit();
    buttonLibExit();

    return 1;
}

void *thread_start(){
    lcdtextwrite("1", "hello!\n");
    lcdtextwrite("2", "Press KEY_BACK button\n");
    show_bmp("start_menual.bmp");
}

//=============GAME1=============//
void *thread_game1(){
    rand1 = rand() % 3;
    fndDisp(111111, 0);
    lcdtextwrite("1", "GAME 1");
    lcdtextwrite("2", "Choose same picture");
    show_bmp("game1_menual.bmp");
    sleep(4);
    if(rand1 == 0){ //game1 첫번째
        show_bmp("game1_q1.bmp");
        sleep(2);
        show_bmp("game1_view1.bmp");
        if((x>180) && (x<480) && (y>70) && (y<290)) show_bmp("wrong.bmp");
        else if((x>540) && (x<830) && (y>70) && (y<290)) show_bmp("correct.bmp");
        else if((x>180) && (x<480) && (y>330) && (y<520)) show_bmp("wrong.bmp");
        else if((x>540) && (x<830) && (y>330) && (y<520)) show_bmp("wrong.bmp");
    }
    else if(rand1 == 1){
        show_bmp("game1_q2.bmp");
        sleep(2);
        show_bmp("game1_view2.bmp");
        if((x>180) && (x<480) && (y>70) && (y<290)) show_bmp("wrong.bmp");
        else if((x>540) && (x<830) && (y>70) && (y<290)) show_bmp("wrong.bmp");
        else if((x>180) && (x<480) && (y>330) && (y<520)) show_bmp("correct.bmp");
        else if((x>540) && (x<830) && (y>330) && (y<520)) show_bmp("wrong.bmp");
    }
    else if(rand1 == 2){
        show_bmp("game1_q3.bmp");
        sleep(2);
        show_bmp("game1_view3.bmp");
        if((x>180) && (x<480) && (y>70) && (y<290)) show_bmp("correct.bmp");
        else if((x>540) && (x<830) && (y>70) && (y<290)) show_bmp("wrong.bmp");
        else if((x>180) && (x<480) && (y>330) && (y<520)) show_bmp("wrong.bmp");
        else if((x>540) && (x<830) && (y>330) && (y<520)) show_bmp("wrong.bmp");
    }
}

//=============GAME2=============//
void *thread_game2(){
    rand2 = rand() % 3;
    fndDisp(222222, 0);
    lcdtextwrite("1", "GAME 2");
    lcdtextwrite("2", "Where is difference?");
    show_bmp("game2_menual.bmp");
    sleep(4);
    if(rand2 == 0){ //game2 첫번째
        show_bmp("game2_q1.bmp");
        sleep(2);
        if(((x>870) && (x<960) && (y>80) && (y<170)) && ((x>420) && (x<480) && (y>85) && (y<170))) show_bmp("correct1.bmp"); 
    }
    else if(rand2 == 1){
        show_bmp("game2_q2.bmp");
        sleep(2);
        if(((x>700) && (x<770) && (y>380) && (y<400)) && ((x>250) && (x<310) && (y>350) && (y<440))) show_bmp("correct2.bmp"); 
    }
    else if(rand2 == 2){
        show_bmp("game2_q3.bmp");
        sleep(2);
        if(((x>880) && (x<945) && (y>310) && (y<380)) && ((x>430) && (x<480) && (y>330) && (y<380))) show_bmp("correct3.bmp");
    }
}

//=============GAME2=============//
void *thread_game3(){
    rand3 = rand() % 3;
    fndDisp(333333, 0);
    lcdtextwrite("1", "GAME 3");
    lcdtextwrite("2", "Odd or Even?");
    show_bmp("game3_menual.bmp");
    sleep(4);
    if(rand2 == 0){ //game2 첫번째
        show_bmp("game3_q.bmp");
        sleep(2);
        if((x>100) && (x<440) && (y>100) && (y<490)) show_bmp("game_correct1.bmp"); //짝
    }
    else if(rand2 == 1){
        show_bmp("game3_q.bmp");
        sleep(2);
        if((x>100) && (x<440) && (y>100) && (y<490)) show_bmp("game_correct1.bmp"); //짝
    }
    else if(rand2 == 2){
        show_bmp("game3_q.bmp");
        sleep(2);
        if((x>575) && (x<930) && (y>100) && (y<490)) show_bmp("game_correct3.bmp"); //홀
    }
}
void *thread_led(){
    while(1)
    {
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, 1);
            sleep(1);
        }
        for (int i = 0; i < 8; i++)
        {
            ledOnOff(i, 0);
            sleep(1);
        }
    }
}

void *thread_button(){
    int returnValue;
    BUTTON_MSG_T msgRx;
    while(1){
        returnValue = msgrcv(msgID, &msgRx, sizeof(msgRx.messageNum), 0, 0);
        if(returnValue<0) printf("Key input fail\n");
        switch(msgRx.keyInput)
        {
            case KEY_HOME:      
                printf("GAME START"); start=1; pthread_create(&gameid[0], NULL, &thread_start, NULL); pthread_detach(gameid[0]);    
            break;
            case KEY_BACK:      
                printf("GAME 1"); game1=1; pthread_create(&gameid[1], NULL, &thread_game1, NULL); pthread_detach(gameid[1]);
            break;
            case KEY_SEARCH:   
                printf("GAME 2"); game2=1; pthread_create(&gameid[2], NULL, &thread_game2, NULL); pthread_detach(gameid[2]); 
            break;
            case KEY_MENU:      
                printf("GAME 3"); game3=1; pthread_create(&gameid[3], NULL, &thread_game3, NULL); pthread_detach(gameid[3]);
            break;

            case KEY_VOLUMEUP:   printf("GAME 4");   break;
            case KEY_VOLUMEDOWN:  printf("GAME FINISH");    break;
        }
    }

}

void *thread_touch(){
    int returnValue1;
    int Messageclean;
    TOUCH_MSG_T msgRxt;

    while(Messageclean != 1) //메세지비우기 
    {
        returnValue1 = msgrcv(msgIDt, &msgRxt, sizeof(msgRxt) - sizeof(long int), 0, IPC_NOWAIT); 
        if (returnValue1 == -1) Messageclean = 1;
    }

    while(1){
        returnValue1 = msgrcv(msgIDt, &msgRxt, sizeof(msgRxt.messageNum), 0, 0);
        if(msgRxt.messageNum == 1) x=msgRxt.touchX;
        else if(msgRxt.messageNum == 2) y = msgRxt.touchY;
        usleep(1000);
    }
}


