#pragma once
class Coords
{
public:
	Coords(int x, int y) : x(x), y(y) {}
	~Coords() {}

	int x;
	int y;
};

inline bool operator==(const Coords& L, const Coords& R) { return L.x == R.x && L.y == R.y; }
inline bool operator!=(const Coords& L, const Coords& R) { return !(L == R); }
