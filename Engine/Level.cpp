#include "Level.h"

Level::Level()
	:
	width(30),
	height(20),
	arr(height, width)
{
	std::string map;

	map += "##############################";
	map += "#............................#";
	map += "#............................#";
	map += "#............................#";
	map += "#....322222222222222.........#";
	map += "#....222222222222223.........#";
	map += "#............................#";
	map += "#............................#";
	map += "#............................#";
	map += "#......23333333332...........#";
	map += "#......23333333332...........#";
	map += "#......23333333333333........#";
	map += "#......2.....................#";
	map += "#............................#";
	map += "#.............11111..........#";
	map += "#......2......11111..........#";
	map += "#......2......11111..........#";
	map += "#......2......11111..........#";
	map += "#......2......11111..........#";
	map += "##############################";


	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++) 
		{
			const char c = map[width * y + x];

			arr.Set(y, x, c);
		}
	}



}

char Level::Get(int x, int y) const
{
	assert(y < arr.GetRows());
	assert(y >= 0);
	assert(x < arr.GetColumns());
	assert(x >= 0);

	return arr.Get(y, x);
}

void Level::Set(int x, int y, char v)
{
	assert(y < arr.GetRows());
	assert(y >= 0);
	assert(x < arr.GetColumns());
	assert(x >= 0);

	arr.Set(y, x, v);
}

int Level::GetWidth() const
{
	return width;
}

int Level::GetHeight() const
{
	return height;
}
