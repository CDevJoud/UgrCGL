#include "Canvas.hpp"

namespace ugr
{
	Canvas::Canvas(Vector2i size)
	{
		re.rect = { 0, 0, short(size.x), (short)size.y };
		re.buffer = new CharPixel[size.x * size.y]{};
		re.screen = size;
		this->InitRenderTarget(re);
	}
	VOID Canvas::SetPosition(Vector2i pos)
	{
		this->pos = pos;
	}
	Vector2i Canvas::GetPosition() const
	{
		return this->pos;
	}
	Vector2i Canvas::GetSize() const
	{
		return this->re.screen;
	}
	CharPixel& Canvas::GetPixel(int x, int y)
	{
		if (this->CheckInBoundaries(Vector2i(x, y), re.rect))
			return this->re.buffer[y * re.screen.x + x];
	}
}