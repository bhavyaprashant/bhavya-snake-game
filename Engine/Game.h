#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
	Board brd;
	Snake snake;
	std::mt19937 rng;
	Goal goal;
	Location delta_loc = { 1,0 };
	//static constexpr int snakeMovePeriod = 10;
	int snakeMovePeriod = 12;
	int snakeMovePeriodMin = 4;
	int snakeMoveCounter = 0;
	int snakeEatCounter = 0;
	bool isGameOver = false;
	bool isGameStarted = false;
	//std::uniform_int_distribution<int> colorDist;
};