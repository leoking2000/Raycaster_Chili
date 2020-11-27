#pragma once
#include <string>
#include "Colors.h"
#include "Array2D.h"
#include "Rectangle.h"


// a 2D array of pixels
class Surface
{
public:
	Surface(const std::string& filename);
	Surface( int width, int height );

	void PutPixel( int x, int y, Color c );
	Color GetPixel( int x, int y ) const;

	int GetWidth() const;
	int GetHeight() const;
	Shape::RectangleI GetRectangle() const;

private:
	int width;
	int height;
	Array2D<Color> pixels;

};

