#pragma once
class Birds
{
private:
	int BirdX = 0;
	int BirdY = 0;
	int KeyPressedBird = 0;
	int BirdTime = 0;
public:
	void BirdMovement(char[30][21]);
	bool GameOver(char[30][21], int[30][21]);
	int GetBirdX();
	void SetKeyPressed(int);
	void JumpBird();
};
