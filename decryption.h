//
// Created by User on 2023-10-10.
//

#ifndef CODINGTABLE_DESCRYPTION_H
#define CODINGTABLE_DESCRYPTION_H

#endif //CODINGTABLE_DESCRYPTION_H

//정적 변수
static int arr[26] = {0};
static char cipher[300] = { };
//static char cipher[300] = "jiywybmdvwyjksnbgmhnkbdmvubgmksoqlznggpbougiysybgmngbwmensjynobjdunvontmdsznxmpubzmumpngdjozjjtbdlbsjiymvgjkmkjympbdmndvumgmoozmvcnxtbdubgxunbywnxmobzomvisojpnyvgoumgid";
static char plain[300] = { };
static char substitution = ' ';
static char target = ' ';
static int x = 30, y = 4, inputPos = 0;

//함수
void gotoxy(int x, int y);
void setConsole();
void setColor(int color);
int startMenu();
int init();
void retry();
void programDw(char input);
void input();
void decryption();