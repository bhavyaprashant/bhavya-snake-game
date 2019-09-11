#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx);
	int GetGridWidth() const;
	int GetGridHeight() const;
	void DrawCell(const Location& loc, Color c);
	bool IsInsideBoard(const Location& loc) const;
	void DrawBorder();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int dimension = 14;
	static constexpr int width = 53;
	static constexpr int height = 39;
	static constexpr int x = 21;
	static constexpr int y = 21;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int cellPadding = 1;
	Graphics& gfx;
};
