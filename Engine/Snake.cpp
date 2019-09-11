#include "Snake.h"

Snake::Snake(const Location& loc)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{14,121,15},
		{14,175,21},
		{14,214,21},
		{14,175,21},
	};

	for (int i = 1; i < nSegmentsMax; i++)
		segments[i].InitBody(bodyColors[i % nBodyColors]);
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		//segments[nSegments].InitBody();
		nSegments++;
	}
}

void Snake::Draw(Board& brd) const
{
	for (int i = 0; i < nSegments; i++)
		segments[i].Draw(brd);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTile(const Location& head_loc) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLocation() == head_loc)
			return true;
	}
	return false;
}

bool Snake::IsInTileExceptEnd(const Location& head_loc) const
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLocation() == head_loc)
			return true;
	}
	return false;
}

int Snake::GetLength()
{
	return nSegments;
}

void Snake::Segment::InitHead(const Location& loc)
{
	this->loc = loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color c)
{
	this->c = c;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
