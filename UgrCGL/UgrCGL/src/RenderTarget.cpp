// O------------------------------------LICENSE--------------------------------------O
// |  MIT License																	 |
// |  																				 |
// |  Copyright(c) 2023 Joud Kandeel												 |
// |  																				 |
// |  Permission is hereby granted, free of charge, to any person obtaining a copy	 |
// |  of this software and associated documentation files(the "Software"), to deal	 |
// |  in the Software without restriction, including without limitation the rights	 |
// |  to use, copy, modify, merge, publish, distribute, sublicense, and /or sell	 |
// |  copies of the Software, and to permit persons to whom the Software is			 |
// |  furnished to do so, subject to the following conditions :						 |
// |  																				 |
// |  The above copyright noticeand this permission notice shall be included in all	 |
// |  copies or substantial portions of the Software.								 |
// |  																				 |
// |  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 |
// |  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 |
// |  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE	 |
// |  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER		 |
// |  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 |
// |  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	 |
// |  SOFTWARE.																		 |
// O---------------------------------------------------------------------------------O

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
	VOID RenderTarget::CalculateClipOn(SHORT x, SHORT y)
	{
		if (x < 0) x = 0;
		if (x > this->re.screen.x) x = this->re.screen.x;
		if (y < 0) y = 0;
		if (y > this->re.screen.y) y = this->re.screen.y;
	}
	VOID RenderTarget::Fill(Vector2i p1, Vector2i p2, SHORT c, Color color)
	{
		this->CalculateClipOn(p1);
		this->CalculateClipOn(p2);
		for (SHORT h = p1.y; h < p2.y; h++)
			for (SHORT w = p1.x; w < p2.x; w++)
				this->SetPixel(Vector2i(w, h), c, color);
	}
	VOID RenderTarget::Fill(ShortRect rect, SHORT c, Color color)
	{
		this->CalculateClipOn(rect.x, rect.y);
		this->CalculateClipOn(rect.width, rect.height);
		for (SHORT h = rect.y; h < rect.height; h++)
			for (SHORT w = rect.x; w < rect.width; w++)
				this->SetPixel(Vector2i(w, h), c, color);
	}
}
