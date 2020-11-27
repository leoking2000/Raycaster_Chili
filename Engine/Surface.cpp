#include "Surface.h"
#include "ChiliWin.h"
#include <fstream>
#include <assert.h>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader),sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));
	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	const bool is32b = bmInfoHeader.biBitCount == 32;


	width = bmInfoHeader.biWidth;
	height = bmInfoHeader.biHeight;

	int yStart;
	int yEnd;
	int dy;
	if (height < 0)
	{
		height = -height;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		yStart = height - 1;
		yEnd = -1;
		dy = -1;
	}

	Array2D<Color> a(width, height);
	pixels = a;

	file.seekg(bmFileHeader.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < width; x++)
		{
			const unsigned char b = file.get();
			const unsigned char g = file.get();
			const unsigned char r = file.get();

			PutPixel(x, y, Color( r,g,b));
			if (is32b) { file.seekg(1, std::ios::cur); }
		}
		if (!is32b) { file.seekg(padding, std::ios::cur); }
	}

}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pixels(width, height)
{
}

void Surface::PutPixel(int x, int y, Color c)
{
	pixels.Set(x, y, c);
}

Color Surface::GetPixel(int x, int y) const
{
	return pixels.Get(x, y);
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

Shape::RectangleI Surface::GetRectangle() const
{
	return Shape::RectangleI(0,width,0,height);
}
