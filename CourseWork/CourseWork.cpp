﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Managers.h"
#include "Birds.h"

using namespace std;

char ScreenParticles[30][21]; // переменная для хранения частиц экрана (пикселей)

int ScreenCheck[30][21]; // переменная для проверки взаимодействия с трубами

int NumberOfDifficulty;

int Time = 0;// переменная для проверки сколько раз был пройден цикл while

void Game();

void Menu();

void EndGame();

void Difficulty();

void Screen();

void Pipes();

void SetColor(int);

void SetBackColor();

Managers* manager = new Managers;

Birds* bird = new Birds;

int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO structCursorInfo;

	GetConsoleCursorInfo(handle, &structCursorInfo);

	structCursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(handle, &structCursorInfo);

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	manager->InputHighscore();

	int HowManyTimesPlayed = 0;

	char Selection;

	while (true)
	{
		if (HowManyTimesPlayed == 0)
			goto play;

		if (HowManyTimesPlayed > 0)
		{
			int scores = 0;

			manager->SetScore(scores);

			cout << "Хотите ли вы сыграть снова? [y/n] ";

			cin >> Selection;

			if (Selection == 'y')
			{
				system("cls");
				goto play;
			}

			if (Selection == 'n')
				goto quit;
		}

	play:

		Menu();

		cin >> Selection;

		switch (Selection)
		{
		case '1':
		{
			Difficulty();
			cin >> NumberOfDifficulty;

			system("cls");

			Game();

			break;
		}

		case '2':
		{
			goto quit;
		}
		default:
		{
			goto play;
		}
		}
		HowManyTimesPlayed++;
	}
quit:
	{
		cout << "Выход";
	}

	return 0;
}

void Game()
{
	int x;

	for (int y = 0; y < 21; y++)// Установка экрана
	{
		for (x = 0; x < 30; x++)
		{
			if (y < 20)
			{
				ScreenParticles[x][y] = ' ';

				ScreenCheck[x][y] = 0;
			}
			if (y == 20)
			{
				ScreenParticles[x][y] = '-';

				ScreenCheck[x][y] = 2;
			}
		}
	}

	ScreenParticles[10][10] = '*';// В этих координатах будет птица

	Screen();

	while (true)
	{
		Sleep(0.15 * 1000);

		Time++;

		if (_kbhit())
		{
			const char s = _getch();

			if (s == ' ')
				bird->SetKeyPressed(1); // Если нажат пробел то функция устанавливает еденицу, это значит то что птица взлетит
		}

		for (x = 0; x < 30; x++)// Установка земли
		{
			ScreenParticles[x][20] = '-';

			ScreenCheck[x][20] = 2;
		}

		bird->BirdMovement(ScreenParticles);

		int birdX = bird->GetBirdX();

		manager->CheckScore(ScreenParticles, birdX);

		if (bird->GameOver(ScreenParticles, ScreenCheck))// Проверка если птица ударилась об трубы
		{
			system("cls");
			goto gameEnd;
		}

		Pipes();
		manager->CheckingScore();
		Screen();

		bird->JumpBird();
	}
gameEnd:
	{
		manager->OutputScore();
		EndGame();
	}
}

void Screen()
{
	SetColor(3);

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD Coordinates;

	Coordinates.X = 0;

	Coordinates.Y = 0;

	SetConsoleCursorPosition(Handle, Coordinates);

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			if (x < 29)
				cout << ScreenParticles[x][y];

			if (x == 29)
				cout << ScreenParticles[x][y] << endl;
		}
	}
	cout << "" << endl;

	cout << "Ваш счёт: " << manager->GetScore();
}

void Pipes()
{
	int x, y, RandomHole;

	if (NumberOfDifficulty == 1)
	{
		if (Time == 10) // если цикл прошел 10 раз, создает новую трубу
		{
			RandomHole = (rand() % 11) + 5; //генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб
			for (y = 0; y < 20; y++)
			{
				ScreenParticles[29][y] = '|'; // устанавливает трубы

				ScreenCheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';// устанавливает дыру в трубе

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 1] = ' ';

			ScreenCheck[29][RandomHole - 1] = 0;

			ScreenCheck[29][RandomHole] = 0;

			ScreenCheck[29][RandomHole + 1] = 0;

			ScreenParticles[29][RandomHole - 2] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 2] = ' ';

			Time = 0;
		}
		else goto ed;
	ed: // передвижение труб
		{
			for (y = 0; y < 20; y++)
			{
				for (x = 0; x < 30; x++)
				{
					if (ScreenParticles[x][y] == '|') // Все трубы передвигаются влево на 1
					{
						if (x > 0)
						{
							ScreenParticles[x - 1][y] = '|';

							ScreenCheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}

						if (x == 0) // если заканчивается экран  трубы исчезают, чтобы предотвратить ошибки
						{
							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
	else if (NumberOfDifficulty == 2)
	{
		if (Time == 10)
		{
			RandomHole = (rand() % 11) + 5;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)
			{
				ScreenParticles[29][y] = '|';

				ScreenCheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 1] = ' ';

			ScreenCheck[29][RandomHole - 1] = 0;

			ScreenCheck[29][RandomHole] = 0;

			ScreenCheck[29][RandomHole + 1] = 0;

			Time = 0;
		}
		else goto md;
	md:
		{
			for (y = 0; y < 20; y++)
			{
				for (x = 0; x < 30; x++)
				{
					if (ScreenParticles[x][y] == '|')
					{
						if (x > 0)
						{
							ScreenParticles[x - 1][y] = '|';

							ScreenCheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}
						if (x == 0)
						{
							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
	else if (NumberOfDifficulty == 3)
	{
		if (Time == 10)
		{
			RandomHole = (rand() % 11) + 7;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)

			{
				ScreenParticles[29][y] = '|';

				ScreenCheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenCheck[29][RandomHole - 1] = 0;

			ScreenCheck[29][RandomHole] = 0;

			ScreenCheck[29][RandomHole + 1] = 0;

			Time = 0;
		}
		else goto hd;
	hd:
		{
			for (y = 0; y < 20; y++)
			{
				for (x = 0; x < 30; x++)
				{
					if (ScreenParticles[x][y] == '|')
					{
						if (x > 0)
						{
							ScreenParticles[x - 1][y] = '|';

							ScreenCheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}
						if (x == 0)
						{
							ScreenParticles[x][y] = ' ';

							ScreenCheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
}

void SetColor(int colorID)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
void SetBackColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE |

		BACKGROUND_BLUE |

		BACKGROUND_GREEN |

		BACKGROUND_RED);
}

void moveto(const int x, int y)
{
	COORD coord;

	HANDLE HStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (HStdOut == INVALID_HANDLE_VALUE)
		return;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(HStdOut, coord);
}

void Menu()
{
	SetColor(5);
	cout << "" << endl;
	cout << " --------------------------------------------------------  " << endl;
	cout << "|                                                        | " << endl;
	cout << "|   **** *    **** **** **** *   *    ***  * ***  ***    | " << endl;
	cout << "|   *    *    *  * *  * *  * *   *    *  * * *  * *  *   | " << endl;
	cout << "|   ***  *    **** **** **** *****    ***  * ***  *  *   | " << endl;
	cout << "|   *    *    *  * *    *      *      *  * * *  * *  *   | " << endl;
	cout << "|   *    **** *  * *    *      *      ***  * *  * ***    | " << endl;
	cout << "|                                                        | " << endl;
	cout << " --------------------------------------------------------  " << endl;
	SetColor(15);
	moveto(20, 10);
	cout << "Рекорд: " << manager->GetHighScore();
	moveto(20, 12);
	cout << "Меню";
	SetColor(11);
	moveto(20, 14);
	cout << "1: Начать игру" << "\n";
	SetColor(12);
	moveto(20, 16);
	cout << "2: Выход" << "\n";
	SetColor(15);
}
void Difficulty()
{
	SetColor(5);
	cout << "--------------------------------------------------------" << endl;
	cout << "|                Выберите сложность:                    |" << endl;
	cout << "|                    1 - Лёгкий                         |" << endl;
	cout << "|                    2 - Средний                        |" << endl;
	cout << "|                    3 - Сложный                        |" << endl;
	cout << "--------------------------------------------------------  " << endl;
	SetColor(15);
}
void EndGame()
{
	SetColor(12);
	cout << "" << endl << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	cout << "|    *****      *     *       * ******       ****  *       * ***** ****    |" << endl;
	cout << "|   *          * *    * *   * * *           *    *  *     *  *     *   *   |" << endl;
	cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *   ****  ****    |" << endl;
	cout << "|   *  *  *  *******  *   *   * *           *    *    * *    *     * *     |" << endl;
	cout << "|    *****  *       * *       * ******       ****      *     ***** *   *   |" << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	SetColor(3);
	moveto(30, 10);
	cout << "Ваш счёт: " << manager->GetScore() << "\n";

	moveto(30, 12);
	cout << "Максимальный рекорд: " << manager->GetHighScore() << endl << endl;
}