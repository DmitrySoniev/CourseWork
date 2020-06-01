#include "Birds.h"
void Birds::SetKeyPressed(int Keypressed)
{
	KeyPressedBird = Keypressed;
}
void Birds::JumpBird()
{
	if (KeyPressedBird > 0)// ���� ������ ������ �� ����� ������� 2 ����
		KeyPressedBird++;

	if (KeyPressedBird == 3) // ����� ����� ����� ������
		KeyPressedBird = 0;
}

void Birds::BirdMovement(char ScreenParticles[30][21])
{
	if (KeyPressedBird > 0)// ���� ������� ������ �� ����� ��������
	{
		BirdTime = 0;

		for (int y = 0; y < 20; y++)// ���� ��� ������ ��������� �����
		{
			for (int x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y > 0)
					{
						ScreenParticles[x][y - 1] = '*';// ����� ����������� �� 1

						ScreenParticles[x][y] = ' ';

						BirdX = x; // ������������� ���������� �� X

						BirdY = y - 1; // ������������� ���������� �� Y

						return;
					}
				}
			}
		}
	}
	else // ���� ������ �� ������, ����� ������
	{
		BirdTime++;

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 30; x++)
			{
				if (ScreenParticles[x][y] == '*')
				{
					if (y < 20)// ���� ����� �� �� �����
					{
						if (BirdTime < 3) // ���� ����� ����� ������ ��� 3, �� ��� ������ �� 1 �������
						{
							ScreenParticles[x][y + 1] = '*';

							ScreenParticles[x][y] = ' ';

							BirdX = x;

							BirdY = y + 1;

							return;
						}
						else if (BirdTime > 2 && BirdTime < 5)// ��� ������ ������ ������� ��� ����� ������� ������
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
bool Birds::GameOver(char ScreenParticles[30][21], int ScreenCheck[30][21]) // �������� ��������� �� �����
{
	int f = 0;

	if (BirdY > 19) // �������� ������� �� ����� �����
	{
		ScreenParticles[BirdX][19] = '*'; // ����� ������������� ����� � ����� ��� ���� ����� ������������� ������

		ScreenParticles[BirdX][20] = '-';

		f = 1;
	}
	else
	{
		if (ScreenCheck[BirdX][BirdY] > 0 && (ScreenParticles[BirdX][BirdY] == '|' || ScreenParticles[BirdX][BirdY] == '*'))// �������� �� �� ��� ����� ��������� �� �����, ����� ����� ���������� ScreenCheck (���������� ����� ����� 2)
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