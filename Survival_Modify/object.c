#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "screen.h"

#define WIDTH 46
#define HEIGHT 31
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define OBSTACLE_COUNT 6

int x[WIDTH * HEIGHT];
int y[WIDTH * HEIGHT];
int item_x, item_y;
int dir, speed, length, score;
int key = 0;
int level = 1;
int obstacle_x[OBSTACLE_COUNT];
int obstacle_y[OBSTACLE_COUNT];

void item() {
	int r = 0;
	int item_crush = 0;
	bool overlapping = false;

	while (1) {
		srand((unsigned)time(NULL) + r);
		item_x = (rand() % (WIDTH - 8)) + 4;  // 스테이지 내부 범위에서 좌표 생성
		item_y = (rand() % (HEIGHT - 8)) + 4;

		// 벽과 충돌하는지 확인
		if (item_x == 3 || item_x == WIDTH - 4 || item_y == 3 || item_y == HEIGHT - 4) {
			r++;
			continue;
		}

		overlapping = false;

		for (int i = 0; i < length; i++) {
			if (item_x == x[i] && item_y == y[i]) {
				overlapping = true;
				break;
			}
		}

		for (int i = 0; i < OBSTACLE_COUNT; i++) {
			if (item_x == obstacle_x[i] && item_y == obstacle_y[i]) {
				overlapping = true;
				break;
			}
		}

		checkLevelUp();

		if (overlapping)
			continue;

		gotoxy(item_x, item_y, "★");
		break;
	}
}


void move(int dir) {
	int i;

	if (x[0] == item_x && y[0] == item_y) {
		score += 10;
		item();
		length++;
		x[length] = x[length - 1];
		y[length] = y[length - 1];
	}

	if (x[0] == 3 || x[0] == WIDTH - 1 || y[0] == 3 || y[0] == HEIGHT - 1) {
		gameOver();
		return;
	}

	// 뱀의 머리와 몸통 충돌 체크
	for (i = 1; i < length; i++) {
		if (x[0] == x[i] && y[0] == y[i]) {
			gameOver();
			return;
		}
	}

	gotoxy(x[length - 1], y[length - 1], "  ");
	for (i = length - 1; i > 0; i--) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}

	gotoxy(x[0], y[0], "○");
	if (dir == LEFT)
		--x[0];
	if (dir == RIGHT)
		++x[0];
	if (dir == UP)
		--y[0];
	if (dir == DOWN)
		++y[0];

	gotoxy(x[i], y[i], "◎");

	checkCollisionWithObstacles();
}


void setSpeedByLevel() {
	switch (level) {
	case 1:
		speed = 250;
		break;
	case 2:
		speed = 150;
		break;
	case 3:
		speed = 100;
		break;
	default:
		speed = 200;
		break;
	}
}

void checkLevelUp() {
	if (score >= 30 && level < 3) {
		level++;
		setSpeedByLevel();

		if (level >= 2) {
			generateObstacles();
			drawObstacles();
		}
	}
}

void generateObstacles() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		srand((unsigned)time(NULL) + i);
		obstacle_x[i] = (rand() % (WIDTH - 8)) + 4;
		obstacle_y[i] = (rand() % (HEIGHT - 8)) + 4;

		// 장애물이 뱀 또는 아이템과 겹치지 않도록 확인
		bool overlapping = false;
		if (obstacle_x[i] == item_x && obstacle_y[i] == item_y) {
			overlapping = true;
		}
		for (int j = 0; j < length; j++) {
			if (obstacle_x[i] == x[j] && obstacle_y[i] == y[j]) {
				overlapping = true;
				break;
			}
		}

		if (overlapping) {
			i--;
			continue;
		}
	}
}

void drawObstacles() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		gotoxy(obstacle_x[i], obstacle_y[i], "■");
	}
}

void checkCollisionWithObstacles() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (x[0] == obstacle_x[i] && y[0] == obstacle_y[i]) {
			gameOver();
			return; // 함수 종료
		}
	}

	// 추가된 부분: 뱀의 몸통과 충돌 체크
	for (int i = 1; i < length; i++) {
		if (x[0] == x[i] && y[0] == y[i]) {
			gameOver();
			return; // 함수 종료
		}
	}
}
