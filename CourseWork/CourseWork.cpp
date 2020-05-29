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

char c[30][21];

int n[30][21];

int highscore;

int NumberOfDifficulty;

int contr, tuk = 0, score = 0, t = 0, bt = 0, birdx = 0, birdy = 0;

bool err;

void game();

void screen();

void pipes();

void bird();

bool gameover();

void checkscore();

void SetColor();

void SetBackColor();

void menu();

void Difficulty();

void endgame();

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

	Input.open("C:/FlappyBird/options.txt");

	if (Input.is_open())
	{
		Input >> highscore;

		Input.close();

		err = false;
	}
	else
	{
		highscore = 0;

		err = true;
	}

	int a = 0, b;

	char sl;

	while (1)
	{
		if (a == 0)
			goto play;

		if (a > 0)
		{
			score = 0;

			cout << "Хотите ли вы сыграть снова? [y/n] ";

			cin >> sl;

			if (sl == 'n')
				goto quit;

			else goto play;
		}

	play:

		/*HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cd;
		cd.X = 0;
		cd.Y = 0;

		SetConsoleCursorPosition(hd, cd);*/

		menu();

		cin >> sl;

		switch (sl)
		{
		case '1':
		{
			Difficulty();

			cin >> NumberOfDifficulty;

			system("cls");

			game();

			break;
		}

		case '2':
		{
			goto quit;
			break;
		}
		default:
		{
			goto play;
			break;
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

void game()
{
	int x, y;

	char s;

	for (y = 0; y < 21; y++)
	{
		for (x = 0; x < 30; x++)
		{
			if (y < 20)
			{
				c[x][y] = ' ';

				n[x][y] = 0;
			}
			if (y == 20)
			{
				c[x][y] = '-';

				n[x][y] = 2;
			}
		}
	}

	c[10][10] = '*';

	screen();

	while (1)
	{
		s = '~';

		Sleep(0.15 * 1000);

		t++;

		if (_kbhit())
		{
			s = _getch();

			if (s != '~') tuk = 1;
		}

		for (x = 0; x < 30; x++)
		{
			c[x][20] = '-';

			n[x][20] = 2;
		}

		bird();

		checkscore();

		if (gameover() == true)
		{
			system("cls");

			goto gameEnd;
		}

		pipes();

		if (score > highscore)
			highscore = score;

		screen();

		if (tuk > 0)
			tuk++;

		if (tuk == 3)
			tuk = 0;
	}
gameEnd:
	{
		if (score > highscore)
			highscore = score;

		if (err == false)
		{
			Output.open("C:/FlappyBird/options.txt");

			Output << highscore;

			Output.close();
		}

		endgame();

		return;
	}
}

void screen()
{
	int x, y;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD Coordinates;

	Coordinates.X = 0;

	Coordinates.Y = 0;

	SetConsoleCursorPosition(Handle, Coordinates);

	for (y = 0; y < 21; y++)
	{
		for (x = 0; x < 30; x++)
		{
			if (x < 29) cout << c[x][y];

			if (x == 29) cout << c[x][y] << endl;
		}
	}
	cout << "" << endl;

	cout << "Ваш счёт: " << score;

	//SetColor(11);
}

void pipes()
{
	int x, y, r;

	if (NumberOfDifficulty == 1)
	{
		if (t == 10)
		{
			r = (rand() % 11) + 5;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб
			for (y = 0; y < 20; y++)
			{
				c[29][y] = '|';

				n[29][y] = 2;
			}
			c[29][r - 1] = ' ';

			c[29][r] = ' ';

			c[29][r + 1] = ' ';

			n[29][r - 1] = 0;

			n[29][r] = 0;

			n[29][r + 1] = 0;

			c[29][r - 2] = ' ';

			c[29][r] = ' ';

			c[29][r + 2] = ' ';

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
					if (c[x][y] == '|')
					{
						if (x > 0)
						{
							c[x - 1][y] = '|';

							n[x - 1][y] = 2;

							c[x][y] = ' ';

							n[x][y] = 0;
						}

						if (x == 0)
						{
							c[x][y] = ' ';

							n[x][y] = 0;
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
			r = (rand() % 11) + 5;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)
			{
				c[29][y] = '|';

				n[29][y] = 2;
			}
			c[29][r - 1] = ' ';

			c[29][r] = ' ';

			c[29][r + 1] = ' ';

			n[29][r - 1] = 0;

			n[29][r] = 0;

			n[29][r + 1] = 0;

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
					if (c[x][y] == '|')
					{
						if (x > 0)
						{
							c[x - 1][y] = '|';

							n[x - 1][y] = 2;

							c[x][y] = ' ';

							n[x][y] = 0;
						}
						if (x == 0)
						{
							c[x][y] = ' ';

							n[x][y] = 0;
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
			r = (rand() % 11) + 7;//генерирует рандомной число, которое будет отвечать где устанвоится дыра для труб

			for (y = 0; y < 20; y++)

			{
				c[29][y] = '|';

				n[29][y] = 2;
			}
			c[29][r - 1] = ' ';

			c[29][r] = ' ';

			n[29][r - 1] = 0;

			n[29][r] = 0;

			n[29][r + 1] = 0;

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
					if (c[x][y] == '|')
					{
						if (x > 0)
						{
							c[x - 1][y] = '|';

							n[x - 1][y] = 2;

							c[x][y] = ' ';

							n[x][y] = 0;
						}
						if (x == 0)
						{
							c[x][y] = ' ';

							n[x][y] = 0;
						}
					}
				}
			}
		}
	}
}

void bird()
{
	int x, y;

	if (tuk > 0)
	{
		bt = 0;

		for (y = 0; y < 20; y++)
		{
			for (x = 0; x < 30; x++)
			{
				if (c[x][y] == '*')
				{
					if (y > 0)
					{
						c[x][y - 1] = '*';

						c[x][y] = ' ';

						birdx = x;

						birdy = y - 1;

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
				if (c[x][y] == '*')
				{
					if (y < 20)
					{
						if (bt < 3)
						{
							c[x][y + 1] = '*';

							c[x][y] = ' ';

							birdx = x;

							birdy = y + 1;

							return;
						}
						else if (bt > 2 && bt < 5)
						{
							c[x][y + 2] = '*';

							c[x][y] = ' ';

							birdx = x;

							birdy = y + 2;

							return;
						}
						else if (bt > 4)
						{
							c[x][y + 3] = '*';

							c[x][y] = ' ';

							birdx = x;

							birdy = y + 3;

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
void checkscore()
{
	int y;

	for (y = 0; y < 20; y++)
	{
		if (c[birdx][y] == '|')
		{
			score++;

			return;
		}
	}
}

bool gameover()
{
	int x, y, f = 0;

	if (birdy > 19)
	{
		c[birdx][19] = '*';

		c[birdx][20] = '-';

		f = 1;

		goto quit;
	}
	else
	{
		if (n[birdx][birdy] > 0 && (c[birdx][birdy] == '|' || c[birdx][birdy] == '*'))
		{
			c[birdx][birdy] = '|';

			c[birdx - 1][19] = '*';

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
void endgame()
{
	screen();
	cout << "" << endl << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	cout << "|    *****      *     *       * ******       ****  *       * ***** ****    |" << endl;
	cout << "|   *          * *    * *   * * *           *    *  *     *  *     *   *   |" << endl;
	cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *   ****  ****    |" << endl;
	cout << "|   *  *  *  *******  *   *   * *           *    *    * *    *     * *     |" << endl;
	cout << "|    *****  *       * *       * ******       ****      *     ***** *   *   |" << endl;
	cout << " --------------------------------------------------------------------------" << endl;
	cout << "" << endl << endl;
	cout << "                        В А Ш  С Ч Ё Т  : " << score << endl << endl;
	cout << "                        М А К С И М А Л Ь Н Ы Й Р Е К О Р Д : " << highscore << endl;
	cout << "" << endl << endl;
}

void menu()
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
	cout << "                     Рекорд:  " << highscore << endl << endl;
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