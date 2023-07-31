#include <RenderTarget.hpp>
namespace ugr
{
	VOID RenderTarget::InitRenderTarget(RenderElements re)
	{
		this->re = re;
	}
	VOID RenderTarget::SetPixel(COORD pos, SHORT c, BYTE color)
	{
		//Check if the position is on the screen coordinates. If it's not don't render it
		if (pos.X >= 0 && pos.X < this->re.screen.X && pos.Y >= 0 && pos.Y < this->re.screen.Y)
		{
			this->re.buffer[pos.Y * this->re.screen.X + pos.X].Char.UnicodeChar = c;
			this->re.buffer[pos.Y * this->re.screen.Y + pos.X].Attributes = color;
		}
	}
}
