#include "Birds.h"
void Birds::SetKeyPressed(int Keypressed)
{
	KeyPressedBird = Keypressed;
}
void Birds::JumpBird()
{
	if (KeyPressedBird > 0)// если кнопка нажата то птица взлетит 2 раза
		KeyPressedBird++;

	if (KeyPressedBird == 3) // после этого птица падает
		KeyPressedBird = 0;
}

void Birds::BirdMovement(char ScreenParticles[30][21])
{
	if (KeyPressedBird > 0)// если клавиша нажата то птица взлетает
	{
		BirdTime = 0;

		for (int y = 0; y < 20; y++)// цикл для поиска координат птицы
		{
			for (int x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y > 0)
					{
						ScreenParticles[x][y - 1] = '*';// птица поднимается на 1

						ScreenParticles[x][y] = ' ';

						BirdX = x; // устанавливает координаты по X

						BirdY = y - 1; // Устанавливает координаты по Y

						return;
					}
				}
			}
		}
	}
	else // если кнопка не нажата, птица падает
	{
		BirdTime++;

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y < 20)// Если птица не на земле
					{
						if (BirdTime < 3) // Если время птицы меньше чем 3, то она падает на 1 пиксель
						{
							ScreenParticles[x][y + 1] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 1;

							return;
						}
						else if (BirdTime > 2 && BirdTime < 5)// Чем больше прошло времени тем птица быстрее падает
						{
							ScreenParticles[x][y + 2] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 2;

							return;
						}
						else if (BirdTime > 4)
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
bool Birds::GameOver(char ScreenParticles[30][21], int ScreenCheck[30][21]) // проверка ударилась ли птица
{
	int f = 0;

	if (BirdY > 19) // проверка ударила ли птица землю
	{
		ScreenParticles[BirdX][19] = '*'; // Снова устанавливает птицу и землю для того чтобы предотвратить ошибки

		ScreenParticles[BirdX][20] = '-';

		f = 1;
	}
	else
	{
		if (ScreenCheck[BirdX][BirdY] > 0 && (ScreenParticles[BirdX][BirdY] == '|' || ScreenParticles[BirdX][BirdY] == '*'))// проверка на то что птица ударилась об трубу, здесь нужна переменная ScreenCheck (координата трубы равна 2)
		{
			ScreenParticles[BirdX][BirdY] = '|';

			ScreenParticles[BirdX - 1][19] = '*';

			f = 1;
		}
	}
	return f == 1;
}
int Birds::GetBirdX()
{
	return BirdX;
}