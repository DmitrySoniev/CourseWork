#define _CRT_SECURE_NO_WARNINGS
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

int ScreenCheck[30][21];

int NumberOfDifficulty;

int Time = 0;// переменная для проверки сколько раз был пройден цикл while

bool ErrorDetection;

void Game();

void Menu();

void EndGame();

void Difficulty();

void Screen();

void Pipes();

bool GameOver();

void CheckScore();

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

	srand(time(0));

	manager->InputHighscore();

	int a = 0;

	char Selection;

	while (true)
	{
		if (a == 0)
			goto play;

		if (a > 0)
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
		a++;
	}
quit:
	{
		cout << "Выход";
	}

	return 0;
}

void Game()
{
	int x, y;

	for (y = 0; y < 21; y++)
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

	ScreenParticles[10][10] = '*';

	Screen();

	while (true)
	{
		Sleep(0.15 * 1000);

		Time++;

		if (_kbhit())
		{
			const char s = _getch();

			if (s != '~')
				bird->SetTuk(1);
		}

		for (x = 0; x < 30; x++)
		{
			ScreenParticles[x][20] = '-';

			ScreenCheck[x][20] = 2;
		}

		bird->BirdMovement(ScreenParticles);

		int birdX = bird->GetBirdX();

		manager->CheckScore(ScreenParticles, birdX);

		if (bird->GameOver(ScreenParticles, ScreenCheck))
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
		if (Time == 10)
		{
			RandomHole = (rand() % 11) + 5; //генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб
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

			ScreenParticles[29][RandomHole - 2] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 2] = ' ';

			Time = 0;

			goto ed;
		}
		else goto ed;
	ed:
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

			goto md;
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

			goto hd;
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