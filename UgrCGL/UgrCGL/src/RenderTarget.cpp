#include <RenderTarget.hpp>
namespace ugr
{
	VOID RenderTarget::InitRenderTarget(RenderElements re)
	{
		this->re = re;
	}
	VOID RenderTarget::SetPixel(Vector2i pos, SHORT c, Color color)
	{
		//Check if the position is on the screen coordinates. If it's not don't render it
		if (pos.x >= 0 && pos.x < this->re.screen.x && pos.y >= 0 && pos.y < this->re.screen.y)
		{
			this->re.buffer[pos.y * this->re.screen.x + pos.x].Char.UnicodeChar = c;
			this->re.buffer[pos.y * this->re.screen.x + pos.x].Color = 0x0F;
		}
	}
	VOID RenderTarget::CalculateClipOn(Vector2i& i)
	{
		if (i.x < 0) i.x = 0;
		if (i.x > this->re.screen.x) i.x = this->re.screen.x;
		if (i.y < 0) i.y = 0;
		if (i.y > this->re.screen.y) i.y = this->re.screen.y;
	}
}
