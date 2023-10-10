#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "decryption.h"

// A = 65, a = 97 -> 97-65 = 32
//암호 문 : jiywybmdvwyjksnbgmhnkbdwmvubgmksoqlznggpbougiysybgmngbwmensjynobjdunvontmdsznxmpubzmumpngdjozjjtbdlbsjiymvgjkmkjympbdmndvumgmoozmvcnxtbdubgxunbywnxmobzomvisojpnyvgoumgid

//전역 변수
int startX = 55, startY = 10;

//메인
int main(void) {
    char command = ' ';
    int posCmmd = 0;
    setConsole();
    posCmmd = startMenu() - 20;
    while (1) {
        scanf("%c", &command);
        if (command == 'r' || command == 'R') {
            system("cls");
            break;
        }
        else if (command == '!') {
            startY = startY + 5;
            gotoxy(45, startY);
            return 0;
        }
        else {
            gotoxy(startX + posCmmd, startY);
        }
    }
    decryption();
}

//좌표 이동
void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//콘솔 창 크기 및 타이틀 설정
void setConsole() {
    system("mode con cols=120 lines=35"); //cols = 가로, lines = 세로
    SetConsoleTitle("복호화 프로그램 (Decryption Program)");
}

//색상 변경
void setColor(int color) {
    if (color == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //글자색 빨강
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //글자색 하얀색
    }
}

//시작 메뉴
int startMenu() {
    char enterStm[40] = "Enter 'R' to start.. >> ";
    gotoxy(startX, startY++);
    printf("<Recommendation>");
    startY = startY + 2; //줄 바꿈
    gotoxy(startX-20, startY++);
    printf("> cmd size : cols = 120, rows = 35");
    startY++;
    gotoxy(startX-20, startY++);
    printf("> To Replace : put lower character for both of target and replacing word");
    startY++;
    gotoxy(startX-20, startY++);
    printf("> To Undo : put Upper character only for target word");
    startY = startY + 2; //줄 바꿈
    gotoxy(startX-10, startY++);
    printf("------------------------------------");
    gotoxy(startX-20, startY);
    printf("%s", enterStm);

    return strlen(enterStm);
}


//초기화면 출력
int init() {
    int printPos = 0;
    int i = 0, j = 0;

    y = 4;
    //입력받은 암호문 갯수 출력
    gotoxy(0, y);
    printf("<암호문 알파벳 갯수>"); //number of the alphabet of the coded message
    for (i=0; i<26; i++) {
        gotoxy(0, ++y);
        printf("%2c = %3d개", i+'A',  arr[i]);
    }

    //메뉴 출력
    y = 4;
    gotoxy(x, y);
    printf("<암호 문자 빈도 순서> (coded message alphabet frequency)");
    gotoxy(x+60, y);
    printf("<프로그램 종료 : !>");
    gotoxy(x, ++y);
    for (i=25; i>=0; i--){
        for (j=0; j<26; j++) {
            if (i == arr[j]) {
                printf("%c ", j+'A');
            }
        }
    }
    gotoxy(x+60, y);
    printf("<초기화 : @>");
    y++;
    gotoxy(x, ++y);
    printf("<일반적인 알파벳 빈도 순서> (general alphabet frequency)");
    gotoxy(x, ++y);
    printf("E T A O I N S H R D L C U M W F G Y P B V K J X Q Z");
    gotoxy(x, ++y);
    printf("E A R I O T N S L C U D P M H G B F Y W K V X Z J Q");

    ++y; //줄 바꿈
    printPos = y;

    //원문 출력
    y = 21;
    gotoxy(x, ++y); printf("원문 > ");
    gotoxy(x, ++y);
    for (i=0; i<strlen(cipher); i++) {
        printf("%c", cipher[i]);
        if ((i % 70 == 0) && (i != 0) ) { //줄바꿈
            gotoxy(x, ++y);
        }
    }

    y++;
    gotoxy(x, ++y);
    printf("For screen error...");
    gotoxy(x, ++y);
    printf(": enter double @ for re-run or double ! to kill the program");

    return printPos;
}

//재실행 화면
void retry () {
    system("cls");
    strcpy(plain, cipher);
    gotoxy(0,0); printf("<암호문>");
    gotoxy(0,1); printf("%s", cipher);
}

//프로그램 종료
void programDw(char input) {
    if (input == '!'){
        gotoxy(x, y+20);
        exit(0);
    }
}

//암호문 입력
void input() {
    int i = 0;
    printf("암호문을 입력하시오. (enter a coded message.)\n");
    scanf("%s", cipher);
    getchar(); //버퍼 비우기
    strcpy(plain, cipher);
    for (i=0; i<strlen(plain); i++) {
        arr[plain[i]-'a'] ++;
    }
}

//해독
void decryption() {
    int i = 0;

    //입력
    input();

    //초기 화면 출력
    y = init();
    inputPos = y;

    //복호모드
    while (1) {
        gotoxy(x, ++y); printf("대상 문자 > ");
        scanf("%c", &target);
        getchar(); //버퍼 비우기
        //프로그램 종료
        programDw(target);
        //재실행
        if (target == '@') {
            retry();
            y = init();
            inputPos = y;
            continue;
        }

        gotoxy(x, ++y); printf("대체 문자 > ");
        scanf("%c", &substitution);
        getchar(); //버퍼 비우기
        if (substitution >= 'a' && substitution <= 'z') {
            substitution -= 32;
        }
        //프로그램 종료
        programDw(substitution);
        //재실행
        if (substitution == '@') {
            retry();
            y = init();
            inputPos = y;
            continue;
        }

        y++; //줄바꿈
        gotoxy(x, ++y); printf("입력 문자 > ");
        gotoxy(x, ++y); printf("target = %c, substitution = %c", target, substitution);

        //치환
        for (i=0; i<strlen(plain); i++) {
            if (plain[i] == target) {
                if (target >= 'A' && target <= 'Z') { //대문자 입력일 경우
                    plain[i] = (char)(substitution+32);
                }
                else {
                    plain[i] = substitution;
                }
            }
        }

        //치환 결과 출력
        y++; //줄바꿈
        gotoxy(x, ++y); printf("치환 결과 > ");
        gotoxy(x, ++y);
        for (i=0; i<strlen(plain); i++) {
            if (plain[i] >= 'A' && plain[i]<='Z') {
                setColor(1);
                printf("%c", plain[i]);
                setColor(0);
            }
            else {
                printf("%c", plain[i]);
            }

            if ((i % 70 == 0) && (i != 0) ) { //줄바꿈
                gotoxy(x, ++y);
            }
        }

        //치환 맵핑 출력
        if (target >= 'A' && target <= 'Z') { //소문자 변환
            target += 32;
        }
        y = (target-'a') + 5; //5 = 초기 값
        gotoxy(10, y);
        printf(" -> %c", substitution);

        y = inputPos; //위치 이동
    }
}