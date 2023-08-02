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
#include <math.h>

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
	VOID RenderTarget::RenderLine(Vector2i p1, Vector2i p2, SHORT c, Color color)
	{
		//Thanks Javidx9 :D
		INT x1 = p1.x; INT x2 = p2.x; INT y1 = p1.y; INT y2 = p2.y;

		INT x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = x2 - x1; dy = y2 - y1;

		dx1 = abs(dx); dy1 = abs(dy);

		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			this->SetPixel(Vector2i(x, y), c, color);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				this->SetPixel(Vector2i(x, y), c, color);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			this->SetPixel(Vector2i(x, y), c, color);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				this->SetPixel(Vector2i(x, y), c, color);
			}
		}
	}
	VOID RenderTarget::RenderLine(ShortRect rect, SHORT c, Color color)
	{
		//Thanks Javidx9 :D
		INT x1 = rect.x; INT x2 = rect.width; INT y1 = rect.y; INT y2 = rect.height;

		INT x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

		dx = x2 - x1; dy = y2 - y1;

		dx1 = abs(dx); dy1 = abs(dy);

		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			this->SetPixel(Vector2i(x, y), c, color);

			for (i = 0; x < xe; i++)
			{
				x = x + 1;
				if (px < 0)
					px = px + 2 * dy1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				this->SetPixel(Vector2i(x, y), c, color);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			this->SetPixel(Vector2i(x, y), c, color);

			for (i = 0; y < ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				this->SetPixel(Vector2i(x, y), c, color);
			}
		}
	}
	VOID RenderTarget::RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT c, Color color)
	{
		this->RenderLine(p1, p2, c, color);
		this->RenderLine(p2, p3, c, color);
		this->RenderLine(p3, p1, c, color);
	}
	VOID RenderTarget::RenderTriangle(VAO p, SHORT c, Color color)
	{
		Vector2i p1(p[0], p[1]);
		Vector2i p2(p[2], p[3]);
		Vector2i p3(p[4], p[5]);
		this->RenderTriangle(p1, p2, p3, c, color);
	}
}
