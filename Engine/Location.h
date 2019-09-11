#pragma once

struct Location
{
	int x;
	int y;
	
	void Add(const Location& val) {
		x += val.x;
		y += val.y;
	}

	bool operator==(const Location& loc) const
	{
		return x == loc.x && y == loc.y;
	}

	bool operator!=(const Location& loc) const
	{
		return !(x == loc.x && y == loc.y);
	}

	Location operator-() const
	{
		return { -x,-y };
	}
};
