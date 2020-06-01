#pragma once
class Managers
{
private:
	int Highscore;

	int Score = 0;

	bool ErrorDetection;
public:

	void SetScore(int);

	void InputHighscore();

	void OutputScore();

	int CheckingScore();

	int GetHighScore();

	int GetScore();

	void CheckScore(char[30][21], int);
};
