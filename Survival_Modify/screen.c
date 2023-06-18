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
		gotoxy(3, i, "��");
		gotoxy(43, i, "��");
	}
	for (int j = 4; j <= 43; j++) {
		gotoxy(j, 3, "��");
		gotoxy(j, 28, "��");
	}
	printf("\n");
}

void printMainMenu() {
	system("cls");
	printf("�������������������������������������������������\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��               S U R V I V A L                ��\n");
	printf("��                 ��       ��                  ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                 1. ���� ����                 ��\n");
	printf("��                 2. ���� ����                 ��\n");
	printf("��                 3. ���� ����                 ��\n");
	printf("��                                              ��\n");
	printf("�������������������������������������������������\n");
}

void introduction() {
	system("cls");
	printf("�������������������������������������������������\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��               S U R V I V A L                ��\n");
	printf("��                 ��       ��                  ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��     �׳� ���� �˰� �ִ� ������ �����̴�.     ��\n");
	printf("��   ���̸� ���� �̻� ������ �ӵ��� ��������.   ��\n");
	printf("��       ���Ҿ� ��ֹ��� �߰��� �����ȴ�.       ��\n");
	printf("��       (����Ű�� ����� ���� �����δ�.)       ��\n");
	printf("��                                              ��\n");
	printf("��           ���� ��Ƴ��⸦ �ٶ��ϴ�.          ��\n");
	printf("��                                              ��\n");
	printf("��  MainMenu�� ���ư��� ������ '1'�� �����ּ���.��\n");
	printf("��                                              ��\n");
	printf("�������������������������������������������������\n");

	r = _getch();
	if (r == '1') {
		printMainMenu();
	}
}

void gameOver() {
	system("cls");
	printf("�������������������������������������������������\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��               S U R V I V A L                ��\n");
	printf("��                 ��       ��                  ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��              G A M E   O V E R               ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��              Your score is %d                ��\n", score);
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("��                                              ��\n");
	printf("�������������������������������������������������\n");
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}