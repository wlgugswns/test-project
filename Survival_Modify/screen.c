#include "screen.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

int r, score;

void gotoxy(SHORT x, SHORT y, char* s) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
	printf("%s", s);
}

void drawMap() {
	for (int i = 3; i <= 28; i++) {
		gotoxy(3, i, "■");
		gotoxy(43, i, "■");
	}
	for (int j = 4; j <= 43; j++) {
		gotoxy(j, 3, "■");
		gotoxy(j, 28, "■");
	}
	printf("\n");
}

void printMainMenu() {
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■               S U R V I V A L                ■\n");
	printf("■                 생       존                  ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                 1. 게임 시작                 ■\n");
	printf("■                 2. 게임 설명                 ■\n");
	printf("■                 3. 게임 종료                 ■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

void introduction() {
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■               S U R V I V A L                ■\n");
	printf("■                 생       존                  ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■     그냥 흔히 알고 있는 지렁이 게임이다.     ■\n");
	printf("■   먹이를 일정 이상 먹으면 속도가 빨라진다.   ■\n");
	printf("■       더불어 장애물도 추가로 생성된다.       ■\n");
	printf("■       (방향키를 사용해 뱀을 움직인다.)       ■\n");
	printf("■                                              ■\n");
	printf("■           오래 살아남기를 바랍니다.          ■\n");
	printf("■                                              ■\n");
	printf("■  MainMenu로 돌아가고 싶으면 '1'을 눌러주세요.■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	r = _getch();
	if (r == '1') {
		printMainMenu();
	}
}

void gameOver() {
	system("cls");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■               S U R V I V A L                ■\n");
	printf("■                 생       존                  ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■              G A M E   O V E R               ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■              Your score is %d                ■\n", score);
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■                                              ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}