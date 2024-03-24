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
#include <Windows.h>
#include <RenderTarget.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <Sprite.hpp>


namespace ugr
{
	VOID RenderTarget::InitRenderTarget(RenderElements re)
	{
		this->re = re;
	}
	VOID RenderTarget::SetPixel(Vector2i pos, CharSurface c, Color color)
	{
		//Check if the position is on the screen coordinates. If it's not don't render it
		if (pos.x >= 0 && pos.x < this->re.screen.x && pos.y >= 0 && pos.y < this->re.screen.y)
		{
			this->re.buffer[pos.y * this->re.screen.x + pos.x].Char.UnicodeChar = c;
			this->re.buffer[pos.y * this->re.screen.x + pos.x].Color = color;
			//WriteConsoleOutputW(this->re.hConsole, PCHAR_INFO(this->re.buffer), { SHORT(this->re.screen.x), SHORT(this->re.screen.y) }, {}, (PSMALL_RECT)&this->re.rect);
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
	VOID RenderTarget::Fill(Vector2i p1, Vector2i p2, CharSurface c, Color color)
	{
		this->CalculateClipOn(p1);
		this->CalculateClipOn(p2);
		for (SHORT h = p1.y; h < p2.y; h++)
			for (SHORT w = p1.x; w < p2.x; w++)
				this->SetPixel(Vector2i(w, h), c, color);
	}
	VOID RenderTarget::Fill(ShortRect rect, CharSurface c, Color color)
	{
		this->CalculateClipOn(rect.x, rect.y);
		this->CalculateClipOn(rect.width, rect.height);
		for (SHORT h = rect.y; h < rect.height; h++)
			for (SHORT w = rect.x; w < rect.width; w++)
				this->SetPixel(Vector2i(w, h), c, color);
	}
	VOID RenderTarget::ClearScreen(CharSurface c, Color color)
	{
		this->Fill(Vector2i(), this->re.screen, c, color);
	}
	VOID RenderTarget::RenderLine(Vector2i p1, Vector2i p2, CharSurface c, Color color)
	{
		//Thanks Javidx9 :D
		INT x1 = p1.x; INT y1 = p1.y; INT x2 = p2.x; INT y2 = p2.y;
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

			SetPixel(Vector2i(x, y), c, color);

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
				SetPixel(Vector2i(x, y), c, color);
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

			SetPixel(Vector2i(x, y), c, color);

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
				SetPixel(Vector2i(x, y), c, color);
			}
		}
	}
	VOID RenderTarget::RenderLine(ShortRect rect, CharSurface c, Color color)
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
	VOID RenderTarget::RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, CharSurface c, Color color)
	{
		this->RenderLine(p1, p2, c, color);
		this->RenderLine(p2, p3, c, color);
		this->RenderLine(p3, p1, c, color);
	}
	VOID RenderTarget::RenderTriangle(VAO* p, CharSurface c, Color color)
	{
		Vector2i p1(p[0], p[1]);
		Vector2i p2(p[2], p[3]);
		Vector2i p3(p[4], p[5]);
		this->RenderTriangle(p1, p2, p3, c, color);
	}
	VOID RenderTarget::RenderQuad(ShortRect rect1, ShortRect rect2, CharSurface c, Color color)
	{
		Vector2i p1 = Vector2i(rect1.x, rect1.y);
		Vector2i p2 = Vector2i(rect1.width, rect1.height);
		Vector2i p3 = Vector2i(rect2.x, rect2.y);
		Vector2i p4 = Vector2i(rect2.width, rect2.height);
		this->RenderLine(p1, p2, c, color);
		this->RenderLine(p2, p3, c, color);
		this->RenderLine(p3, p4, c, color);
		this->RenderLine(p4, p1, c, color);
	}
	VOID RenderTarget::RenderQuad(ShortRect rect, CharSurface c, Color color)
	{
		Vector2i p[4];
		Vector2i size = Vector2i(rect.width, rect.height);
		Vector2i pos = Vector2i(rect.x, rect.y);
		p[0] = Vector2i(0, 0);
		p[1].x = size.x;
		p[2] = size;
		p[3].y = size.y;

		this->RenderLine(p[0] + pos, p[1] + pos, c, color);
		this->RenderLine(p[1] + pos, p[2] + pos, c, color);
		this->RenderLine(p[2] + pos, p[3] + pos, c, color);
		this->RenderLine(p[3] + pos, p[0] + pos, c, color);
	}
	VOID RenderTarget::RenderQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, CharSurface c, Color color)
	{
		this->RenderLine(p1, p2, c, color);
		this->RenderLine(p2, p3, c, color);
		this->RenderLine(p3, p4, c, color);
		this->RenderLine(p4, p1, c, color);
	}
	VOID RenderTarget::RenderText(Vector2i pos, LPCSTR str, Color color, CGLFlags _flags_)
	{
		Vector2i oldPos = pos;
		if (this->CheckInBoundaries(pos, this->re.rect))
		{
			if (_flags_ & RT_ENABLE_NEWLINE_DETECTION)
			{
				std::vector<std::string> lines;
				std::string line;
				for (INT i = 0; i < strlen(str) + 1; i++)
				{
					if (str[i] == 0x0A || str[i] == 0x00)
					{
						lines.push_back(line);
						line.clear();
						//i++;
					}
					else
						line += str[i];
				}

				for (auto& _str : lines)
				{
					for (INT i = 0; i < _str.size(); i++)
					{
						if (_flags_ & RT_ENABLE_CORRECT_CONVERT)
							this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = this->CorrectConversion(_str[i]);
						else
							this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.AsciiChar = _str[i];
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Color = color;
					}
					pos.y++;
				}
			}
			else
			{
				for (INT i = 0; i < strlen(str); i++)
				{
					if (_flags_ & RT_ENABLE_CORRECT_CONVERT)
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = this->CorrectConversion(str[i]);
					else
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.AsciiChar = str[i];
					this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Color = color;
				}
			}
		}
	}
	VOID RenderTarget::RenderText(Vector2i pos, LPCWSTR str, Color color, CGLFlags _Flags_)
	{
		if (this->CheckInBoundaries(pos, this->re.rect))
		{
			if (_Flags_ & RT_ENABLE_NEWLINE_DETECTION)
			{
				std::vector<std::wstring> lines;
				std::wstring line;
				for (INT i = 0; i < lstrlenW(str) + 1; i++)
				{
					if (str[i] == 0x0A || str[i] == 0x00)
					{
						lines.push_back(line);
						line.clear();
					}
					else
						line += str[i];
				}

				for (auto& _str : lines)
				{
					for (INT i = 0; i < _str.size(); i++)
					{
						if (_Flags_ & RT_ENABLE_CORRECT_CONVERT)
							this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = this->CorrectConversion(_str[i]);
						else
							this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = _str[i];
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Color = color;
					}
					pos.y++;
				}
			}
			else
			{
				//Need to Fix For buffer overflow
				for (INT i = 0; i < lstrlenW(str); i++)
				{
					if (_Flags_ & RT_ENABLE_CORRECT_CONVERT)
					{
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = this->CorrectConversion(str[i]);
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Color = color;
					}
					else if (this->CheckInBoundaries(Vector2i(pos.x + i, pos.y), { SHORT(i), 0, this->re.rect.width, this->re.rect.height }))
					{
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Char.UnicodeChar = str[i];
						this->re.buffer[(pos.y * this->re.screen.x + pos.x) + i].Color = color;
					}
				}
			}
		}
	}
	VOID RenderTarget::RenderSprite(Vector2i pos, Sprite* s)
	{
		for(int x = pos.x; x < s->GetSize().x; x++)
			for (int y = pos.y; y < s->GetSize().y; y++)
			{
				CharPixel cp = s->GetPixel(x, y);
				this->SetPixel(Vector2i(x, y), cp.Char.UnicodeChar, cp.Color);
			}
	}
	VOID RenderTarget::RenderCircle(Vector2i p1, INT radius, CharSurface c, Color color, VOID(*VertexShader)(INT& p, INT& x, INT& y))
	{
		//Flags will be added later!
		INT xc = p1.x;
		INT yc = p1.y;
		INT x = 0;
		INT y = radius;
		INT p = 3 - 2 * radius;
		
		if (!radius) return;
		while (y >= x)
		{
			this->SetPixel(Vector2i(xc - x, yc - y), c, color);
			this->SetPixel(Vector2i(xc - y, yc - x), c, color);
			this->SetPixel(Vector2i(xc + y, yc - x), c, color);
			this->SetPixel(Vector2i(xc + x, yc - y), c, color);
			this->SetPixel(Vector2i(xc - x, yc + y), c, color);
			this->SetPixel(Vector2i(xc - y, yc + x), c, color);
			this->SetPixel(Vector2i(xc + y, yc + x), c, color);
			this->SetPixel(Vector2i(xc + x, yc + y), c, color);
			if(VertexShader != NULL)
				VertexShader(p, x, y);
			else
				p += (p < 0) ? 4 * x++ + (6) : 4 * (x++ - y--) + 10;
		}
	}
	VOID RenderTarget::RasterizeTriangle(Vector2i p1, Vector2i p2, Vector2i p3, CharSurface c, Color color)
	{
		INT x1 = p1.x;
		INT y1 = p1.y;

		INT x2 = p2.x;
		INT y2 = p2.y;

		INT x3 = p3.x;
		INT y3 = p3.y;
		auto SWAP = [](INT& x, INT& y) { INT t = x; x = y; y = t; };
		auto drawline = [&](INT sx, INT ex, INT ny) { for (INT i = sx; i <= ex; i++) SetPixel(Vector2i(i, ny), c, color); };

		INT t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		INT signx1, signx2, dx1, dy1, dx2, dy2;
		INT e1, e2;
		// Sort vertices
		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

		t1x = t2x = x1; y = y1;   // Starting poINTs
		dx1 = (INT)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (INT)(y2 - y1);

		dx2 = (INT)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (INT)(y3 - y1);

		if (dy1 > dx1) {   // swap values
			SWAP(dx1, dy1);
			changed1 = TRUE;
		}
		if (dy2 > dx2) {   // swap values
			SWAP(dy2, dx2);
			changed2 = TRUE;
		}

		e2 = (INT)(dx2 >> 1);
		// Flat top, just process the second half
		if (y1 == y2) goto next;
		e1 = (INT)(dx1 >> 1);

		for (INT i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;//t1x += signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
			// Move line
		next1:
			// process second line until y value is about to change
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;//t2x += signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);    // Draw line from min to max poINTs found on the y
										 // Now increase y
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		// Second half
		dx1 = (INT)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (INT)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {   // swap values
			SWAP(dy1, dx1);
			changed1 = TRUE;
		}
		else changed1 = FALSE;

		e1 = (INT)(dx1 >> 1);

		for (INT i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			// process first line until y value is about to change
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }//t1x += signx1;
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:
			// process second line until y value is about to change
			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x; if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x; if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}
	VOID RenderTarget::RasterizeCircle(Vector2i p1, INT r, CharSurface c, Color color, void(*VertexShader)(int& p, int& x, int& y))
	{
		INT yc = p1.y;
		INT xc = p1.x;
		// Taken from wikipedia
		INT x = 0;
		INT y = r;
		INT p = 3 - 2 * r;
		if (!r) return;

		auto drawline = [&](INT sx, INT ex, INT ny)
		{
			for (INT i = sx; i <= ex; i++)
				SetPixel(Vector2i(i, ny), c, color);
		};

		while (y >= x)
		{
			// Modified to draw scan-lines instead of edges
			drawline(xc - x, xc + x, yc - y);
			drawline(xc - y, xc + y, yc - x);
			drawline(xc - x, xc + x, yc + y);
			drawline(xc - y, xc + y, yc + x);
			if (VertexShader != NULL)
				VertexShader(p, x, y);
			else
				p += (p < 0) ? 4 * x++ + (6) : 4 * (x++ - y--) + 10;
		}
	}
	VOID RenderTarget::RasterizeQuad(ShortRect rect, CharSurface c, Color color)
	{
		Vector2i p[4];
		p[0] = Vector2i(0, 0);
		p[1] = Vector2i(rect.width, 0);
		p[2] = Vector2i(rect.width, rect.height);
		p[3] = Vector2i(0, rect.height);
		auto pos = Vector2i(rect.x, rect.y);
		this->Fill(p[0] + pos, p[2] + pos, c, color);
	}
	VOID RenderTarget::RasterizeQuad(ShortRect rect1, ShortRect rect2, CharSurface c, Color color)
	{
		Vector2i p1 = Vector2i(rect1.x, rect1.y);
		Vector2i p2 = Vector2i(rect1.width, rect1.height);
		Vector2i p3 = Vector2i(rect2.x, rect2.y);
		Vector2i p4 = Vector2i(rect2.width, rect2.height);

		this->RasterizeTriangle(p1, p2, p3, c, color);
		this->RasterizeTriangle(p1, p4, p3, c, color);
	}
	BOOL RenderTarget::CheckInBoundaries(Vector2i pos, ShortRect rect)
	{
		return (pos.x >= rect.x && pos.x < rect.width && pos.y >= rect.y && pos.y < rect.height);
	}
	SHORT RenderTarget::CorrectConversion(BYTE c)
	{
		return 0x00 | c;
	}
}
