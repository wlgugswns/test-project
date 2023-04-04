#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

int print_title_screen()
{
	printf("********************************************\n");
	printf("*                                          *\n");
	printf("*                                          *\n");
	printf("*               지렁이 게임                *\n");
	printf("*              (Snake Bite)                *\n");
	printf("*                                          *\n");
	printf("*   1. 게임 시작                           *\n");
	printf("*   2. 게임 설명                           *\n");
	printf("*   3. 게임 랭킹 보기                      *\n");
	printf("*   4. 게임 종료 (esc)                     *\n");
	printf("********************************************\n");


	return 0;
}

int print_introduction_screen()
{
	printf("********************************************\n");
	printf("*          게임 설명 화면입니다.           *\n");
	printf("********************************************\n");
	printf("*    타이틀 화면으로 돌아갈까요? (Y/N)     *\n");

	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int print_stage_screen(int width, int height)
{
	int i, j;
	gotoxy(100, 100);
	for (i = 0; i < width; i++)
	{
		printf("*");
	}
	printf("\n");

	for (i = 1; i < height - 1; i++)
	{
		printf("*");
		for (j = 1; j < width - 1; j++)
		{
			printf(" ");
		}
		printf("*\n");
	}

	for (i = 0; i < width; i++)
	{
		printf("*");
	}
	printf("\n");

	printf("********************************************\n");
	printf("*    타이틀 화면으로 돌아갈까요? (Y/N)     *\n");
	return 0;
}


int main()
{
	int game_state = 0;
	int is_game_running = 1;
	int refresh = 0;
	while (is_game_running)
	{
		char key_input = 0;
		switch (game_state)
		{
		case 0:
			if (refresh == 0)
			{
				print_title_screen();
				refresh = 10;
			}
			key_input = 0;
			key_input = _getch();

			if (key_input == '1')
			{
				game_state = 1;
				refresh = 1;
			}
			else if (key_input == '2')
			{
				game_state = 2;
				refresh = 2;
			}
			else if (key_input == '4' || key_input == 27)
			{
				is_game_running = 0;
			}
			break;

		case 1:
			if (refresh == 1)
			{
				print_stage_screen(50, 25);
				refresh = 10;
			}
			key_input = 0;
			key_input = _getch();

			if (key_input == 'y')
			{
				game_state = 0;
				refresh = 0;
			}

			break;

		case 2:
			if (refresh == 2)
			{
				print_introduction_screen();
				refresh = 10;
			}
			key_input = 0;
			key_input = _getch();

			if (key_input == 'y')
			{
				game_state = 0;
				refresh = 0;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}