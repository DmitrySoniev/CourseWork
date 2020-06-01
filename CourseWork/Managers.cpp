#include "Managers.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <iomanip>

std::ifstream Input;

std::ofstream Output;

int Managers::CheckingScore()
{
	if (Score > Highscore)
	{
		Highscore = Score;
		return Highscore;
	}
}

void Managers::SetScore(int score)
{
	Score = score;
}
void Managers::InputHighscore()
{
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
}

int Managers::GetHighScore()
{
	return Highscore;
}

int Managers::GetScore()
{
	return Score;
}
void Managers::CheckScore(char ScreenParticles[30][21], int BirdX)
{
	for (int y = 0; y < 20; y++)
	{
		if (ScreenParticles[BirdX][y] == '|')
		{
			Score++;

			return;
		}
	}
}
void Managers::OutputScore() // Запись рекорда в файл
{
	if (!ErrorDetection)
	{
		Output.open("C:/FlappyBird/Score.txt");

		Output << Highscore;

		Output.close();
	}
}