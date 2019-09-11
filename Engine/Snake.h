#pragma once
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(Color c);
		void MoveBy(const Location& delta_loc);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool IsInTile(const Location& head_loc) const;
	bool IsInTileExceptEnd(const Location& head_loc) const;
	int GetLength();
private:
	static constexpr Color headColor = Colors::Yellow;
	//static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};