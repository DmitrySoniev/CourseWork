#include "Birds.h"
void Birds::SetTuk(int Tuk)
{
	tuk = Tuk;
}
void Birds::JumpBird()
{
	if (tuk > 0)
		tuk++;

	if (tuk == 3)
		tuk = 0;
}

void Birds::BirdMovement(char ScreenParticles[30][21])
{
	if (tuk > 0)
	{
		bt = 0;

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 30; x++)
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

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 30; x++)
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
bool Birds::GameOver(char ScreenParticles[30][21], int ScreenCheck[30][21])
{
	int f = 0;

	if (BirdY > 19)
	{
		ScreenParticles[BirdX][19] = '*';

		ScreenParticles[BirdX][20] = '-';

		f = 1;
	}
	else
	{
		if (ScreenCheck[BirdX][BirdY] > 0 && (ScreenParticles[BirdX][BirdY] == '|' || ScreenParticles[BirdX][BirdY] == '*'))
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