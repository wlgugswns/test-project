#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

#define WIDTH 46
#define HEIGHT 31
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define OBSTACLE_COUNT 6

void title();
void drawMap();
void start();
void item();
void gameOver();
void move(int dir);
void setSpeedByLevel();
void checkLevelUp();
void generateObstacles();
void drawObstacles();
void checkCollisionWithObstacles();
void introduction();

void gotoxy(int x, int y, const char* s) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
	printf("%s", s);
}


int x[WIDTH * HEIGHT];
int y[WIDTH * HEIGHT];
int item_x, item_y;
int dir, speed, length, score;
int key = 0;
int level = 1;
int obstacle_x[OBSTACLE_COUNT];
int obstacle_y[OBSTACLE_COUNT];

void printMainMenu()
{
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

void title() {
	int choice = 0;

	while (1) {
		printMainMenu(); // ���� �޴� ���

		while (!_kbhit()) {} // Ű �Է� ���
		key = _getch();

		switch (key) {
		case '1':
			start(); // ���� ����
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

void gotoxy(SHORT x, SHORT y, char* s) {
	COORD pos = { x,y };//x,y�� ��ǥ�� �����ϴ� ����ü
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//Ŀ���� cmdâ���� �̵���Ű�� �Լ�
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
		gotoxy(x[i], y[i], "��");
	}
	gotoxy(x[0], y[0], "��");
	item();

	setSpeedByLevel();
	generateObstacles();
	drawObstacles();

	while (1) {
		if (_kbhit())
			do { key = _getch(); } while (key == 224);
		Sleep(speed);

		switch (key) {
		case LEFT:
		case RIGHT:
		case UP:
		case DOWN:
			if ((dir == LEFT && key != RIGHT) || (dir == RIGHT && key != LEFT) || (dir == UP && key != DOWN) || (dir == DOWN && key != UP))
				dir = key;
			key = 0;
			break;
		case ESC:
			exit(0);
		}
		move(dir);
		checkCollisionWithObstacles();
	}
}

void introduction()
{
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

	key = _getch();
	if (key == '1') {
		printMainMenu();
	}
}

void item() {
	int r = 0;
	int item_crush = 0;

	while (1) {
		srand((unsigned)time(NULL) + r);
		item_x = (rand() % (WIDTH - 8)) + 4;  // �������� ���� �������� ��ǥ ����
		item_y = (rand() % (HEIGHT - 8)) + 4;

		// ���� �浹�ϴ��� Ȯ��
		if (item_x == 3 || item_x == WIDTH - 4 || item_y == 3 || item_y == HEIGHT - 4) {
			r++;
			continue;
		}

		for (int i = 0; i < length; i++) {
			if (item_x == x[i] && item_y == y[i]) {
				item_crush = 1;
				r++;
				break;
			}
		}

		checkLevelUp();

		if (item_crush == 1)
			continue;

		gotoxy(item_x, item_y, "��");
		break;
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

	return;
}

void move(int dir) {
	int i;

	if (x[0] == item_x && y[0] == item_y) { //item�� �浹���� ���
		score += 10;
		item(); //���ο� food �߰�
		length++;
		x[length] = x[length - 1]; //�����ϼ��� ��ǥ���� ���ؾ��ϱ� ������
		//���� �ִ� ������ǥ���� ���� ������ ��ǥ���� �־��� 
		y[length] = y[length - 1];
	}
	if (x[0] == 3 || x[0] == WIDTH - 1 || y[0] == 3 || y[0] == HEIGHT - 1) {
		gameOver();
		return; //gameOver���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ� �ʱ�ȭ
	}

	gotoxy(x[length - 1], y[length - 1], "  ");
	//���� ��ǥ�� �����϶����� �ǵ��� ���� ��������� -> ����ó��
	for (i = length - 1; i > 0; i--) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}

	gotoxy(x[0], y[0], "��");
	if (dir == LEFT)
		--x[0];
	if (dir == RIGHT)
		++x[0];
	if (dir == UP)
		--y[0];
	if (dir == DOWN)
		++y[0];

	gotoxy(x[i], y[i], "��");
}

void setSpeedByLevel()
{
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

void checkLevelUp()
{
	if (score >= 30 && level < 3) {
		level++;
		setSpeedByLevel();

		if (level >= 2) {
			generateObstacles();
			drawObstacles();
		}
	}
}

void drawObstacles()
{
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		gotoxy(obstacle_x[i], obstacle_y[i], "��");
	}
}

void generateObstacles() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		srand((unsigned)time(NULL) + i);
		obstacle_x[i] = (rand() % (WIDTH - 8)) + 4;
		obstacle_y[i] = (rand() % (HEIGHT - 8)) + 4;

		// ��ֹ��� �� �Ǵ� �����۰� ��ġ�� �ʵ��� Ȯ��
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

void checkCollisionWithObstacles() {
	for (int i = 0; i < OBSTACLE_COUNT; i++) {
		if (x[0] == obstacle_x[i] && y[0] == obstacle_y[i]) {
			gameOver();
			exit(0);
		}
	}
}

int main() {
	title();
	
	return 0;
}