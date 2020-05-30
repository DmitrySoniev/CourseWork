#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream Input;

ofstream Output;

char ScreenParticles[30][21]; // переменная для хранения частиц экрана (пикселей)

int ScreenScheck[30][21];

int Highscore;

int NumberOfDifficulty;

int tuk = 0, Score = 0, t = 0, bt = 0, BirdX = 0, BirdY = 0;

bool ErrorDetection;

void Game();

void Screen();

void Pipes();

void Bird();

bool GameOver();

void CheckScore();

void SetColor();

void SetBackColor();

void Menu();

void Difficulty();

void EndGame();

int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO structCursorInfo;

	GetConsoleCursorInfo(handle, &structCursorInfo);

	structCursorInfo.bVisible = FALSE;

	SetConsoleCursorInfo(handle, &structCursorInfo);

	SetConsoleCP(1251);

	SetConsoleOutputCP(1251);

	/*SetConsoleTextAttribute(handle, 11);*/

	/*system("color ");*/

	srand(time(0));

	Input.open("C:/FlappyBird/Score.txt");

	if (Input.is_open())
	{
		Input >> Highscore;

		Input.close();

		ErrorDetection = false;
	}
	else
	{
		Highscore = 0;

		ErrorDetection = true;
	}

	int a = 0;

	char Selection;

	while (true)
	{
		if (a == 0)
			goto play;

		if (a > 0)
		{
			Score = 0;

			cout << "Хотите ли вы сыграть снова? [y/n] ";

			cin >> Selection;

			if (Selection == 'y')
				goto play;

			if (Selection == 'n')
				goto quit;

			// else goto play;
		}

	play:

		/*HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cd;
		cd.X = 0;
		cd.Y = 0;

		SetConsoleCursorPosition(hd, cd);*/

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

				ScreenScheck[x][y] = 0;
			}
			if (y == 20)
			{
				ScreenParticles[x][y] = '-';

				ScreenScheck[x][y] = 2;
			}
		}
	}

	ScreenParticles[10][10] = '*';

	Screen();

	while (true)
	{
		Sleep(0.15 * 1000);

		t++;

		if (_kbhit())
		{
			const char s = _getch();

			if (s != '~')
				tuk = 1;
		}

		for (x = 0; x < 30; x++)
		{
			ScreenParticles[x][20] = '-';

			ScreenScheck[x][20] = 2;
		}

		Bird();

		CheckScore();

		if (GameOver() == true)
		{
			system("cls");

			goto gameEnd;
		}

		Pipes();

		if (Score > Highscore)
			Highscore = Score;

		Screen();

		if (tuk > 0)
			tuk++;

		if (tuk == 3)
			tuk = 0;
	}
gameEnd:
	{
		if (Score > Highscore)
			Highscore = Score;

		if (ErrorDetection == false)
		{
			Output.open("C:/FlappyBird/Score.txt");

			Output << Highscore;

			Output.close();
		}

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
			if (x < 29) cout << ScreenParticles[x][y];

			if (x == 29) cout << ScreenParticles[x][y] << endl;
		}
	}
	cout << "" << endl;

	cout << "Ваш счёт: " << Score;

	//SetColor(11);
}

void Pipes()
{
	int x, y, RandomHole;

	if (NumberOfDifficulty == 1)
	{
		if (t == 10)
		{
			RandomHole = (rand() % 11) + 5; //генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб
			for (y = 0; y < 20; y++)
			{
				ScreenParticles[29][y] = '|';

				ScreenScheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 1] = ' ';

			ScreenScheck[29][RandomHole - 1] = 0;

			ScreenScheck[29][RandomHole] = 0;

			ScreenScheck[29][RandomHole + 1] = 0;

			ScreenParticles[29][RandomHole - 2] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 2] = ' ';

			t = 0;

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

							ScreenScheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}

						if (x == 0)
						{
							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
	else if (NumberOfDifficulty == 2)
	{
		if (t == 10)
		{
			RandomHole = (rand() % 11) + 5;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)
			{
				ScreenParticles[29][y] = '|';

				ScreenScheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenParticles[29][RandomHole + 1] = ' ';

			ScreenScheck[29][RandomHole - 1] = 0;

			ScreenScheck[29][RandomHole] = 0;

			ScreenScheck[29][RandomHole + 1] = 0;

			t = 0;

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

							ScreenScheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}
						if (x == 0)
						{
							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
	else if (NumberOfDifficulty == 3)
	{
		if (t == 10)
		{
			RandomHole = (rand() % 11) + 7;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)

			{
				ScreenParticles[29][y] = '|';

				ScreenScheck[29][y] = 2;
			}
			ScreenParticles[29][RandomHole - 1] = ' ';

			ScreenParticles[29][RandomHole] = ' ';

			ScreenScheck[29][RandomHole - 1] = 0;

			ScreenScheck[29][RandomHole] = 0;

			ScreenScheck[29][RandomHole + 1] = 0;

			t = 0;

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

							ScreenScheck[x - 1][y] = 2;

							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}
						if (x == 0)
						{
							ScreenParticles[x][y] = ' ';

							ScreenScheck[x][y] = 0;
						}
					}
				}
			}
		}
	}
}

void Bird()
{
	int x, y;

	if (tuk > 0)
	{
		bt = 0;

		for (y = 0; y < 20; y++)
		{
			for (x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y > 0)
					{
						ScreenParticles[x][y - 1] = '*';

						ScreenParticles[x][y] = ' ';

						BirdX = x;

						BirdY = y - 1;

						return;
					}
				}
			}
		}
	}
	else
	{
		bt++;

		for (y = 0; y < 20; y++)
		{
			for (x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y < 20)
					{
						if (bt < 3)
						{
							ScreenParticles[x][y + 1] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 1;

							return;
						}
						else if (bt > 2 && bt < 5)
						{
							ScreenParticles[x][y + 2] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 2;

							return;
						}
						else if (bt > 4)
						{
							ScreenParticles[x][y + 3] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 3;

							return;
						}
					}
					else
					{
						return;
					}
				}
			}
		}
	}
}
void CheckScore()
{
	int y;

	for (y = 0; y < 20; y++)
	{
		if (ScreenParticles[BirdX][y] == '|')
		{
			Score++;

			return;
		}
	}
}

bool GameOver()
{
	int f = 0;

	if (BirdY > 19)
	{
		ScreenParticles[BirdX][19] = '*';

		ScreenParticles[BirdX][20] = '-';

		f = 1;

		goto quit;
	}
	else
	{
		if (ScreenScheck[BirdX][BirdY] > 0 && (ScreenParticles[BirdX][BirdY] == '|' || ScreenParticles[BirdX][BirdY] == '*'))
		{
			ScreenParticles[BirdX][BirdY] = '|';

			ScreenParticles[BirdX - 1][19] = '*';

			f = 1;

			goto quit;
		}
	}
quit:
	if (f == 1)
		return true;
	else
		return false;
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
void EndGame()
{
	Screen();
	cout << "" << endl << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	cout << "|    *****      *     *       * ******       ****  *       * ***** ****    |" << endl;
	cout << "|   *          * *    * *   * * *           *    *  *     *  *     *   *   |" << endl;
	cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *   ****  ****    |" << endl;
	cout << "|   *  *  *  *******  *   *   * *           *    *    * *    *     * *     |" << endl;
	cout << "|    *****  *       * *       * ******       ****      *     ***** *   *   |" << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	cout << "" << endl << endl;
	cout << "                        В А Ш  С Ч Ё Т  : " << Score << endl << endl;
	cout << "                        М А К С И М А Л Ь Н Ы Й Р Е К О Р Д : " << Highscore << endl;
	cout << "" << endl << endl;
}

void Menu()
{
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
	cout << "" << endl << endl;
	cout << "                     Рекорд:  " << Highscore << endl << endl;
	cout << "" << endl << endl;
	cout << "                     М Е Н Ю:    " << endl << endl;
	cout << "                  1: Начать игру  " << endl << endl;

	cout << "                  2: Выход        " << endl << endl;
}
void Difficulty()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "|                Выберите сложность:                    |" << endl;
	cout << "|                    1 - Лёгкий                         |" << endl;
	cout << "|                    2 - Средний                        |" << endl;
	cout << "|                    3 - Сложный                        |" << endl;
	cout << "--------------------------------------------------------  " << endl;
}