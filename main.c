#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "decryption.h"

// A = 65, a = 97 -> 97-65 = 32
//��ȣ �� : jiywybmdvwyjksnbgmhnkbdwmvubgmksoqlznggpbougiysybgmngbwmensjynobjdunvontmdsznxmpubzmumpngdjozjjtbdlbsjiymvgjkmkjympbdmndvumgmoozmvcnxtbdubgxunbywnxmobzomvisojpnyvgoumgid

//���� ����
int startX = 55, startY = 10;

//����
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

//��ǥ �̵�
void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//�ܼ� â ũ�� �� Ÿ��Ʋ ����
void setConsole() {
    system("mode con cols=120 lines=35"); //cols = ����, lines = ����
    SetConsoleTitle("��ȣȭ ���α׷� (Decryption Program)");
}

//���� ����
void setColor(int color) {
    if (color == 1) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //���ڻ� ����
    }
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //���ڻ� �Ͼ��
    }
}

//���� �޴�
int startMenu() {
    char enterStm[40] = "Enter 'R' to start.. >> ";
    gotoxy(startX, startY++);
    printf("<Recommendation>");
    startY = startY + 2; //�� �ٲ�
    gotoxy(startX-20, startY++);
    printf("> cmd size : cols = 120, rows = 35");
    startY++;
    gotoxy(startX-20, startY++);
    printf("> To Replace : put lower character for both of target and replacing word");
    startY++;
    gotoxy(startX-20, startY++);
    printf("> To Undo : put Upper character only for target word");
    startY = startY + 2; //�� �ٲ�
    gotoxy(startX-10, startY++);
    printf("------------------------------------");
    gotoxy(startX-20, startY);
    printf("%s", enterStm);

    return strlen(enterStm);
}


//�ʱ�ȭ�� ���
int init() {
    int printPos = 0;
    int i = 0, j = 0;

    y = 4;
    //�Է¹��� ��ȣ�� ���� ���
    gotoxy(0, y);
    printf("<��ȣ�� ���ĺ� ����>"); //number of the alphabet of the coded message
    for (i=0; i<26; i++) {
        gotoxy(0, ++y);
        printf("%2c = %3d��", i+'A',  arr[i]);
    }

    //�޴� ���
    y = 4;
    gotoxy(x, y);
    printf("<��ȣ ���� �� ����> (coded message alphabet frequency)");
    gotoxy(x+60, y);
    printf("<���α׷� ���� : !>");
    gotoxy(x, ++y);
    for (i=25; i>=0; i--){
        for (j=0; j<26; j++) {
            if (i == arr[j]) {
                printf("%c ", j+'A');
            }
        }
    }
    gotoxy(x+60, y);
    printf("<�ʱ�ȭ : @>");
    y++;
    gotoxy(x, ++y);
    printf("<�Ϲ����� ���ĺ� �� ����> (general alphabet frequency)");
    gotoxy(x, ++y);
    printf("E T A O I N S H R D L C U M W F G Y P B V K J X Q Z");
    gotoxy(x, ++y);
    printf("E A R I O T N S L C U D P M H G B F Y W K V X Z J Q");

    ++y; //�� �ٲ�
    printPos = y;

    //���� ���
    y = 21;
    gotoxy(x, ++y); printf("���� > ");
    gotoxy(x, ++y);
    for (i=0; i<strlen(cipher); i++) {
        printf("%c", cipher[i]);
        if ((i % 70 == 0) && (i != 0) ) { //�ٹٲ�
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

//����� ȭ��
void retry () {
    system("cls");
    strcpy(plain, cipher);
    gotoxy(0,0); printf("<��ȣ��>");
    gotoxy(0,1); printf("%s", cipher);
}

//���α׷� ����
void programDw(char input) {
    if (input == '!'){
        gotoxy(x, y+20);
        exit(0);
    }
}

//��ȣ�� �Է�
void input() {
    int i = 0;
    printf("��ȣ���� �Է��Ͻÿ�. (enter a coded message.)\n");
    scanf("%s", cipher);
    getchar(); //���� ����
    strcpy(plain, cipher);
    for (i=0; i<strlen(plain); i++) {
        arr[plain[i]-'a'] ++;
    }
}

//�ص�
void decryption() {
    int i = 0;

    //�Է�
    input();

    //�ʱ� ȭ�� ���
    y = init();
    inputPos = y;

    //��ȣ���
    while (1) {
        gotoxy(x, ++y); printf("��� ���� > ");
        scanf("%c", &target);
        getchar(); //���� ����
        //���α׷� ����
        programDw(target);
        //�����
        if (target == '@') {
            retry();
            y = init();
            inputPos = y;
            continue;
        }

        gotoxy(x, ++y); printf("��ü ���� > ");
        scanf("%c", &substitution);
        getchar(); //���� ����
        if (substitution >= 'a' && substitution <= 'z') {
            substitution -= 32;
        }
        //���α׷� ����
        programDw(substitution);
        //�����
        if (substitution == '@') {
            retry();
            y = init();
            inputPos = y;
            continue;
        }

        y++; //�ٹٲ�
        gotoxy(x, ++y); printf("�Է� ���� > ");
        gotoxy(x, ++y); printf("target = %c, substitution = %c", target, substitution);

        //ġȯ
        for (i=0; i<strlen(plain); i++) {
            if (plain[i] == target) {
                if (target >= 'A' && target <= 'Z') { //�빮�� �Է��� ���
                    plain[i] = (char)(substitution+32);
                }
                else {
                    plain[i] = substitution;
                }
            }
        }

        //ġȯ ��� ���
        y++; //�ٹٲ�
        gotoxy(x, ++y); printf("ġȯ ��� > ");
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

            if ((i % 70 == 0) && (i != 0) ) { //�ٹٲ�
                gotoxy(x, ++y);
            }
        }

        //ġȯ ���� ���
        if (target >= 'A' && target <= 'Z') { //�ҹ��� ��ȯ
            target += 32;
        }
        y = (target-'a') + 5; //5 = �ʱ� ��
        gotoxy(10, y);
        printf(" -> %c", substitution);

        y = inputPos; //��ġ �̵�
    }
}