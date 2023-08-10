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

#include <TextBox.hpp>
#include <vector>
#include <string>

namespace ugr
{
	class TextBox::pImpl
	{
	public:
		Vector2i m_size;
		RenderElements re;
		Vector2i m_pos;

		std::vector<std::wstring> m_vecLines;
		int m_nVisibleHeight; // Height of the visible region
		int m_nScrollPosition = 0; // Current scroll position
		SHORT m_n16Color = 0x00;


		Vector2i m_scrollbarPosition;
		int m_nScrollBarHeight;
	};
	TextBox::TextBox()
	{
		this->This = new pImpl;
	}
	TextBox::~TextBox()
	{
		This->m_vecLines.clear();
		This->m_vecLines.shrink_to_fit();
		delete This;
	}
	VOID TextBox::Clean()
	{
		This->m_vecLines.clear();
		This->m_vecLines.shrink_to_fit();
		delete This;
	}
	VOID TextBox::CreateBox(Vector2i size)
	{
		This->m_size = size;
		This->m_scrollbarPosition.x = size.x;
		This->m_scrollbarPosition.y = 1;
		This->m_nScrollBarHeight = size.y - 2;
		This->m_nVisibleHeight = size.y;
		This->m_pos = Vector2i(1, 1);
		This->re.buffer = new CharPixel[This->m_size.x * This->m_size.y]{};;
		This->re.screen = This->m_size;
		This->re.rect = { 0, 0, SHORT(This->m_size.x), SHORT(This->m_size.y) };
		this->InitRenderTarget(This->re);
	}
	VOID TextBox::SetPosition(Vector2i pos)
	{
		This->m_pos = pos;
	}
	VOID TextBox::AddLine(LPCWSTR str)
	{
		This->m_vecLines.push_back(str);
	}
	VOID TextBox::SetTextBoxColor(SHORT color)
	{
		This->m_n16Color = color;
	}
	INT TextBox::GetVisibileHeight() const
	{
		return This->m_nVisibleHeight;
	}
	INT TextBox::GetScrollPosition() const
	{
		return This->m_nScrollPosition;
	}
	INT TextBox::GetScrollBarHeight() const
	{
		return This->m_nScrollBarHeight;
	}
	Vector2i TextBox::GetScrollBarPosition() const
	{
		return This->m_scrollbarPosition;
	}
	Color TextBox::GetColor() const
	{
		return This->m_n16Color;
	}
	VOID TextBox::MoveUp()
	{
		This->m_nScrollPosition--;
	}
	VOID TextBox::MoveDown()
	{
		This->m_nScrollPosition++;
	}
	INT TextBox::GetLinesSize() const
	{
		return This->m_vecLines.size();
	}
	VOID TextBox::ResetTextBox()
	{
		This->m_vecLines.clear();
		This->m_vecLines.shrink_to_fit();
	}
	VOID TextBox::RenderSilent()
	{
		Vector2i p1 = This->m_pos;
		Vector2i p2 = This->m_pos + This->m_size;
		this->ClearScreen();
		// Draw the visible lines
		for (int y = 0; y < This->m_nVisibleHeight; y++)
		{
			int lineIndex = y + This->m_nScrollPosition;
			if (lineIndex >= 0 && lineIndex < static_cast<int>(This->m_vecLines.size()))
			{
				this->RenderText(Vector2i(0, y), This->m_vecLines[lineIndex].c_str(), 0x0F);
			}
		}
	}
	Vector2i TextBox::GetSize() const
	{
		return This->m_size;
	}
	Vector2i TextBox::GetPosition() const
	{
		return This->m_pos;
	}
	CharPixel TextBox::GetCharPixel(INT val)
	{
		return This->re.buffer[val];
	}
}
