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
static pthread_t buzzer_ID;
static pthread_t textlcd_ID;
static pthread_t gameid[4];

static int msgID = 0;
static int msgIDt = 0;
int game;
int rand1, rand2, rand3;
int start; int x, y;

void *thread_led();
void *thread_button();
void *thread_touch();
void *thread_start();
void *thread_game1();
void *thread_game2();
void *thread_game3();
void *thread_buzzer();
void *thread_textlcd();

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
    pthread_create(&buzzer_ID, NULL, &thread_buzzer, NULL);
    pthread_create(&textlcd_ID, NULL, &thread_textlcd, NULL);

    pthread_join(textlcd_ID, NULL);
    pthread_join(buzzer_ID, NULL);
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

void *thread_textlcd(){
    if(start == 1) {
        lcdtextwrite("1", "Hello");  
        lcdtextwrite("2", "Press KEYBACK button");
    }
    else if(game == 1){
        lcdtextwrite("1", "GAME 1");  
        lcdtextwrite("2", "Choose same picture");
    }
    else if(game == 2){
        lcdtextwrite("1", "GAME 2");  
        lcdtextwrite("2", "Where is difference?");
    }
    else if(game == 3){
        lcdtextwrite("1", "GAME 3");  
        lcdtextwrite("2", "Odd or Even?");
    }
}

void *thread_buzzer(){
    buzzerPlaySong(5);
    sleep(1);
    buzzerStopSong();
}

void *thread_start(){
    show_bmp("start_menual.bmp");
    pthread_exit(NULL);
}

//=============GAME1=============//
void *thread_game1(){
    //sleep(1);
    if(game == 1){
        rand1 = rand() % 3;
        fndDisp(111111, 0);
        sleep(1);
        show_bmp("game1_menual.bmp");
        sleep(4);
        if(rand1 == 0){ //game1 첫번째
            show_bmp("game1_q1.bmp");
            usleep(100000);
            show_bmp("game1_view1.bmp");
            sleep(2);
            while(game == 1){
                if((x>180) && (x<480) && (y>70) && (y<290)) { show_bmp("wrong.bmp"); sleep(10); }
                else if((x>540) && (x<830) && (y>70) && (y<290)) { show_bmp("wrong.bmp"); sleep(10); }
                else if((x>180) && (x<480) && (y>330) && (y<520)) { show_bmp("correct.bmp"); sleep(10); }
                else if((x>540) && (x<830) && (y>330) && (y<520)) { show_bmp("wrong.bmp"); sleep(10); }
            }
            sleep(1);
        }
        else if(rand1 == 1){
            show_bmp("game1_q2.bmp");
            usleep(100000);
            show_bmp("game1_view2.bmp");
            sleep(2);
            while(game == 1){
                if((x>180) && (x<480) && (y>70) && (y<290)) { show_bmp("wrong.bmp"); sleep(10); }
                else if((x>540) && (x<830) && (y>70) && (y<290)) {show_bmp("correct.bmp"); sleep(10); }
                else if((x>180) && (x<480) && (y>330) && (y<520)) {show_bmp("wrong.bmp");  sleep(10); }
                else if((x>540) && (x<830) && (y>330) && (y<520)) {show_bmp("wrong.bmp"); sleep(10); }
            }
            sleep(1);
        }
    
        else if(rand1 == 2){
            show_bmp("game1_q3.bmp");
            usleep(100000);
            show_bmp("game1_view3.bmp");
            sleep(2);
            while(game == 1){
                if((x>180) && (x<480) && (y>70) && (y<290)) {show_bmp("wrong.bmp");sleep(10); }
                else if((x>540) && (x<830) && (y>70) && (y<290)) {show_bmp("wrong.bmp");sleep(10); }
                else if((x>180) && (x<480) && (y>330) && (y<520)) {show_bmp("wrong.bmp");sleep(10); }
                else if((x>540) && (x<830) && (y>330) && (y<520)) {show_bmp("correct.bmp");sleep(10); }
            }
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//=============GAME2=============//
void *thread_game2(){
    //sleep(1);
    if(game == 2){
        rand2 = rand() % 3;
        fndDisp(222222, 0);
        sleep(1);
        show_bmp("game2_menual.bmp");
        sleep(4);
        if(rand2 == 0){ //game2 첫번째
            show_bmp("game2_q1.bmp");
            sleep(2);
            while(game == 2){
                if(((x>870) && (x<960) && (y>80) && (y<170)) || ((x>420) && (x<480) && (y>85) && (y<170))){ 
                    show_bmp("correct1.bmp"); 
                    sleep(10);
                }
            }
            sleep(1);
        }
        
        else if(rand2 == 1){
            show_bmp("game2_q2.bmp");
            sleep(2);
            while(game == 2){
                if(((x>700) && (x<770) && (y>380) && (y<400)) || ((x>250) && (x<310) && (y>350) && (y<440))){
                    show_bmp("correct2.bmp"); 
                    sleep(10);
                }
            }
            sleep(1);
        }
        
        else if(rand2 == 2){
            show_bmp("game2_q3.bmp");
            sleep(2);
            while(game == 2){
                if(((x>880) && (x<945) && (y>310) && (y<380)) || ((x>430) && (x<480) && (y>330) && (y<380))){ 
                    show_bmp("correct3.bmp");
                    sleep(10);
                }
            }
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//=============GAME3=============//
void *thread_game3(){
    //sleep(1);
    if(game == 3){
        rand3 = rand() % 3;
        fndDisp(333333, 0);
        sleep(1);
        show_bmp("game3_menual.bmp");
        sleep(4);
        if(rand2 == 0){ //game3 첫번째
            show_bmp("game3_q.bmp");
            sleep(2);
            while(game == 3){ 
                if((x>100) && (x<440) && (y>100) && (y<490)) {
                    show_bmp("game3_correct1.bmp"); //짝
                    sleep(10);
                }
                else if((x>575) && (x<930) && (y>100) && (y<490)){
                    show_bmp("wrong.bmp");
                    sleep(10);
                }
            }
            sleep(1);
        }
        else if(rand2 == 1){
            show_bmp("game3_q.bmp");
            sleep(2);
            while(game == 3){
                if((x>100) && (x<440) && (y>100) && (y<490)) {
                    show_bmp("game3_correct1.bmp");//짝
                    sleep(10);
                }
                else if((x>575) && (x<930) && (y>100) && (y<490)){
                    show_bmp("wrong.bmp");
                    sleep(10);
                }
            }
            sleep(1);
        }
        else if(rand2 == 2){
            show_bmp("game3_q.bmp");
            sleep(2);
            while(game == 3){
                if((x>575) && (x<930) && (y>100) && (y<490)) {
                    show_bmp("game3_correct3.bmp"); //홀
                    sleep(10);
                }
                else if((x>100) && (x<440) && (y>100) && (y<490)){
                    show_bmp("wrong.bmp");
                    sleep(10);
                }
            }
            sleep(1);
        }
    }
    pthread_exit(NULL);
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
        returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0, 0);
        if(returnValue<0) printf("Key input fail\n");
        switch(msgRx.keyInput)
        {
            case KEY_HOME:      
                printf("GAME START"); pthread_create(&gameid[0], NULL, &thread_start, NULL); start=1; pthread_detach(gameid[0]);    
            break;
            case KEY_BACK:      
                printf("GAME 1"); pthread_create(&gameid[1], NULL, &thread_game1, NULL); game=1; pthread_detach(gameid[1]);
            break;
            case KEY_SEARCH:   
                printf("GAME 2"); pthread_create(&gameid[2], NULL, &thread_game2, NULL); game=2; pthread_detach(gameid[2]); 
            break;
            case KEY_MENU:      
                printf("GAME 3"); pthread_create(&gameid[3], NULL, &thread_game3, NULL); game=3; pthread_detach(gameid[3]);
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
        returnValue1 = msgrcv(msgIDt, &msgRxt, sizeof(msgRxt) - sizeof(long int), 0, 0);
        if(msgRxt.messageNum == 1) {
            printf("\nx : %d\n", msgRxt.touchX);
            x = msgRxt.touchX;
        }
        else if(msgRxt.messageNum == 2) {
            printf("\ny : %d\n", msgRxt.touchY);
            y = msgRxt.touchY;
        }
        else printf("other");
        usleep(1000);
    }
}