#include "game.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>


#define WIDTH 46
#define HEIGHT 31
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define OBSTACLE_COUNT 6

int response = 0;
int dir, speed, length, score;
int x[WIDTH * HEIGHT];
int y[WIDTH * HEIGHT];

void title() {
	int choice = 0;

	while (1) {
		printMainMenu(); // 메인 메뉴 출력

		while (!_kbhit()) {} // 키 입력 대기
		response = _getch();

		switch (response) {
		case '1':
			start(); // 게임 시작
			break;
		case '2':
			introduction();
			break;
		case '3':
			exit(0);
			break;
		}
	}
}

void start() {
	system("cls");
	drawMap();
	while (_kbhit())
		_getch();

	dir = LEFT;
	speed = 200;
	length = 5;
	score = 0;

	for (int i = 0; i < length; i++) {
		x[i] = WIDTH / 2 + i;
		y[i] = HEIGHT / 2;
		gotoxy(x[i], y[i], "○");
	}
	gotoxy(x[0], y[0], "◎");
	item();

	setSpeedByLevel();
	generateObstacles();
	drawObstacles();

	while (1) {
		if (_kbhit())
			do { response = _getch(); } while (response == 224);

		Sleep(speed);

		switch (response) {
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir == LEFT && response != RIGHT) || (dir == RIGHT && response != LEFT) || (dir == UP && response != DOWN) || (dir == DOWN && response != UP))
				dir = response;
			response = 0;
			break;
		case ESC:
			exit(0);
		}
		move(dir);
		checkCollisionWithObstacles();
	}
}



int main()
{
	hideCursor();
	title();
	start();
	return 0;
}