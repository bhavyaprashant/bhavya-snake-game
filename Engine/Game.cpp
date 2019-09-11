#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	goal(rng, brd, snake),
	brd(gfx),
	snake({ 2,2 }),
	//colorDist(0, 255),
	rng(std::random_device()())
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isGameStarted)
	{
		if (!isGameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				const Location new_delta_loc = { 0,-1 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				const Location new_delta_loc = { 0,1 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				const Location new_delta_loc = { -1,0 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				const Location new_delta_loc = { 1,0 };
				if (delta_loc != -new_delta_loc || snake.GetLength() <= 2)
				{
					delta_loc = new_delta_loc;
				}
			}

			snakeMoveCounter++;
			if (snakeMoveCounter >= snakeMovePeriod)
			{
				snakeMoveCounter = 0;
				const Location nextMove = snake.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(nextMove) || snake.IsInTileExceptEnd(nextMove))
				{
					isGameOver = true;
				}
				else
				{
					bool isEating = nextMove == goal.GetLocation();
					if (isEating)
					{
						snake.Grow();
						snakeEatCounter++;
						if (snakeEatCounter % 2 == 0)
							snakeMovePeriod = std::max(snakeMovePeriod - 1, snakeMovePeriodMin);
					}
					snake.MoveBy(delta_loc);
					if (isEating)
					{
						goal.Respawn(rng, brd, snake);
					}
				}
			}
		}
	}
	else
	{
		isGameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}

void Game::ComposeFrame()
{
	if (isGameStarted)
	{
		for(int x=0;x<brd.GetGridWidth();x++)
			for (int y = 0; y < brd.GetGridHeight(); y++)
			{
				Location loc = { x,y };
				Color c(50, 0, 75);
				if ((x % 2 == 0 && y%2==0) || (x % 2 == 1 && y % 2 == 1))
					brd.DrawCell(loc, c);
			}
		brd.DrawBorder();
		snake.Draw(brd);
		goal.Draw(brd);
		if (isGameOver)
		{
			SpriteCodex::DrawGameOver(366, 252, gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(0, 0, gfx);
	}
	/*
		//std::uniform_int_distribution<int> colorDist(0, 255);
		for (int x = 0; x < brd.GetGridWidth(); x++)
			for (int y = 0; y < brd.GetGridHeight(); y++) {
				Location loc = { x,y };
				Color c(colorDist(rng), colorDist(rng), colorDist(rng));
				brd.DrawCell(loc, c);
			}
	*/
}
