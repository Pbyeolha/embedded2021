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
#include "bitmap.h"

#define  INPUT_DEVICE_LIST   "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int stage1, stage2, stage3, stage4 = 0;
int start = 0;
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
    /*
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
    */
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

    int msgID = buttonLibInit();
    //int msgIDt = touchLibInit();
    int returnValue = 0; 
    int rand1, rand2, rand3, rand4;
    BUTTON_MSG_T messageRx;

    returnValue=msgrcv(msgID, &messageRx, sizeof(messageRx.messageNum), 0 , 0);
   
    if(returnValue<0)
    printf("Key input fail\n");

    switch(messageRx.keyInput)
    {
        case KEY_HOME:      printf("GAME START"); start=1;     break;
        case KEY_BACK:      printf("GAME 1"); stage1=1;     break;
        case KEY_SEARCH:   printf("GAME 2"); stage2=1;     break;
        case KEY_MENU:      printf("GAME 3"); stage3=1;     break;
        case KEY_VOLUMEUP:   printf("GAME 4"); stage4=1;  break;
        case KEY_VOLUMEDOWN:  printf("GAME FINISH");    break;
    }
    printf("\n");
    if(start ==1){ //start
        lcdtextwrite("1", "hello!\n");
        lcdtextwrite("2", "Press KEY_BACK button\n");
        show_bmp("start_menual.bmp");
    }  

 //=============Game 1=============//
    if(stage1 ==1){ //game1
        rand1 = rand() % 3;
        fndDisp(1111111, 0);
        lcdtextwrite("1", "GAME 1");
        lcdtextwrite("2", "Chosse same picture");
        show_bmp("game1_menual.bmp");
        sleep(4);
        if(rand1 == 0){ //첫번째 사진 맞추기
            show_bmp("game1_question1.bmp");
            sleep(3);
            show_bmp("game1_1_1.bmp");
            sleep(2);
            show_bmp("game1_1_2.bmp");
            sleep(2);
            show_bmp("game1_1_3.bmp");
            sleep(2);
            if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage1 == 1){ //첫번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        }
        else if(rand1 == 1){ //두번째 사진 맞추기
            show_bmp("game1_question2.bmp");
            sleep(3);
            show_bmp("game1_2_1.bmp");
            sleep(2);
            show_bmp("game1_2_2.bmp");
            sleep(2);
            show_bmp("game1_2_3.bmp");
            sleep(2);
            if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage1 == 1){ //첫번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else { //세번째 사진 맞추기
            show_bmp("game1_question3.bmp");
            sleep(3);
            show_bmp("game1_3_1.bmp");
            sleep(2);
            show_bmp("game1_3_2.bmp");
            sleep(2);
            show_bmp("game1_3_3.bmp");
            sleep(2);
            if(stage1 == 1){ //첫번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        } 
    }       

 //=============Game 2=============//
    else if(stage2 ==1){ //game2
        rand2 = rand() % 3;
        fndDisp(222222, 0);
        lcdtextwrite("1", "GAME 2");
        lcdtextwrite("2", "Who Am I");
        show_bmp("game2_menual.bmp");
        sleep(4);
        if(rand1 == 0){ //첫번째 사진 맞추기
            show_bmp("game2_question1.bmp");
            sleep(3);
            show_bmp("game2_1_1.bmp");
            sleep(2);
            show_bmp("game2_1_2.bmp");
            sleep(2);
            show_bmp("game2_1_3.bmp");
            sleep(2);
            if(stage1 == 1){ //cjt번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        }
        else if(rand1 == 1){ //두번째 사진 맞추기
            show_bmp("game2_question2.bmp");
            sleep(3);
            show_bmp("game2_2_1.bmp");
            sleep(2);
            show_bmp("game2_2_2.bmp");
            sleep(2);
            show_bmp("game2_2_3.bmp");
            sleep(2);
            if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage1 == 1){ //첫번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else { //세번째 사진 맞추기
            show_bmp("game2_question3.bmp");
            sleep(3);
            show_bmp("game2_3_1.bmp");
            sleep(2);
            show_bmp("game2_3_2.bmp");
            sleep(2);
            show_bmp("game2_3_3.bmp");
            sleep(2);
            if(stage2 == 1){ //두번째 button 눌렸을 때
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage3 == 1){ //세번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage1 == 1){ //첫번째 button 눌렸을 때
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        } 
    }

 //=============Game 3=============//
    else if(stage3 ==1){ //game3
        rand3 = rand() % 3;
        fndDisp(333333, 0);
        lcdtextwrite("1", "GAME 3");
        lcdtextwrite("2", "Spot the Difference");
        show_bmp("game3_menual.bmp");
        sleep(4);
        if(rand1 == 0){ //첫번째 사진 맞추기
            show_bmp("game3_question1.bmp");
            sleep(3);
            show_bmp("game3_1_1.bmp");
            sleep(2);
            show_bmp("game3_1_2.bmp");
            sleep(2);
            show_bmp("game3_1_3.bmp");
            sleep(2);
            if(stage1 == 1){ //첫번째, 틀린 개수 2개
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage2 == 1){ //두번째, 틀린 개수 3개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage3 == 1){ //세번째, 틀린 개수 4개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        }
        else if(rand3 == 1){ //두번째 사진 맞추기
            show_bmp("game3_question2.bmp");
            sleep(3);
            show_bmp("game3_2_1.bmp");
            sleep(2);
            show_bmp("game3_2_2.bmp");
            sleep(2);
            show_bmp("game3_2_3.bmp");
            sleep(2);
            if(stage3 == 1){ //세번째, 틀린 개수 4개
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage1 == 1){ //첫번째, 틀린 개수 2개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage2 == 1){ //두번째, 틀린 개수 3개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        else { //세번째 사진 맞추기
            show_bmp("game3_question3.bmp");
            sleep(3);
            show_bmp("game3_3_1.bmp");
            sleep(2);
            show_bmp("game3_3_2.bmp");
            sleep(2);
            show_bmp("game3_3_3.bmp");
            sleep(2);
            if(stage2 == 1){ //세번째, 틀린 개수 3개
                show_bmp("correct.bmp");
                lcdtextwrite("1", "Correct!");
                lcdtextwrite("2", "You're right!");
            }
            else if(stage1 == 1){ //첫번째, 틀린 개수 2개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "Sorry");
                lcdtextwrite("2", "You're wrong");
            }
            else if(stage3 == 1){ //두번째, 틀린 개수 4개
                show_bmp("wrong.bmp");
                lcdtextwrite("1", "sorry");
                lcdtextwrite("2", "You're wrong");
            }
        } 
    }
 //=============Game 4=============//
    else if(stage4 ==1){ //game4
        rand4 = rand() % 3; //random으로 0, 1, 2생성
        //구슬 개수 0, 3, 4
        fndDisp(444444, 0);
        lcdtextwrite("1", "GAME 4");
        lcdtextwrite("2", "Odd or Even");
        show_bmp("game4_menual.bmp");;
        sleep(4);
        if(rand4 == 0){
            show_bmp("game4_question1.bmp"); //0개
            sleep(3);
            if(stage1 == 1){ //첫번째 버튼 눌렸을 때
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Odd");
                show_bmp("wrong.bmp"); //틀렸습니다
            }
            else if(stage2 == 1){
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Even");
                show_bmp("right_1.bmp"); //맞았고, 손바닥 펴진 상태 (0개 있는 거 알려줌)
            }
        }
        else if(rand4 == 1) {
            show_bmp("game4_question2.bmp"); //3개
            sleep(3);
            if(stage1==1){
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Odd");
                show_bmp("right_2.bmp");
            }
            else if(stage2 == 1){
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Even");
                show_bmp("wrong.bmp");
            }
        }
        else {
            show_bmp("game4_question3.bmp"); //4개
            sleep(3);
            if(stage1==1){
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Odd");
                show_bmp("wrong.bmp");
            }
            else if(stage2 ==1){
                lcdtextwrite("1", "You select");
                lcdtextwrite("2", "Even");
                show_bmp("right_3.bmp");
            }
        }    
    }
    

    //=============exit=============//
    ledLibExit();
    buttonLibExit();
    textlcdLibexit();
    buzzerExit();
    //touchLibExit();

    return 0;
}