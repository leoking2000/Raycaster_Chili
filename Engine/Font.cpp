#include "Font.h"

Font::Font(const std::string& filename, Color chroma)
	:
	surface(filename),
	glyphWidth(surface.GetWidth() / nColumns),
	glyphHeight(surface.GetHeight() / nRows),
	chroma(chroma)
{
	assert(glyphWidth * nColumns == surface.GetWidth());
	assert(glyphHeight * nRows == surface.GetHeight());
}

void Font::DrawText(int x, int y, const std::string& text, Color color, Graphics& gfx) const
{
	int curX = x;
	int curY = y;

	for (auto c : text)
	{
		if (c == '\n')
		{
			curX = x;
			curY += glyphHeight;
			continue;
		}
		if (c >= firstChar + 1 && c <= lastChar)
		{
			gfx.DrawSpriteSubstitute(curX, curY,MapGlyphRect(c), surface, chroma);
		}
		curX += glyphWidth;
	}

}

Shape::RectangleI Font::MapGlyphRect(char c) const
{
	assert(c >= firstChar && c <= lastChar);
	const int glyphIndex = c - ' ';
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;

	return Shape::RectangleI({ float(xGlyph * glyphWidth), float(yGlyph * glyphHeight) }, glyphWidth, glyphHeight);
}
