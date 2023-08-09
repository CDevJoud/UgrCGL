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
#include <Button.hpp>

namespace ugr
{
	VOID Button::SetTitle(LPCWSTR t, BYTE col)
	{
		this->m_title = t;
		this->m_n8TitleColor = col;
		this->m_size.x = lstrlenW(t) + 2;
	}
	VOID Button::SetColor(BYTE color)
	{
		this->m_n8Color = color;
	}
	VOID Button::SetPosition(Vector2i pos)
	{
		this->m_pos = pos;
	}
	VOID Button::ProcessEvents(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos();
		INT y1 = mousePos.y - 1;
		INT y2 = m_posRelativeToConsole.y - 1;
		//Check for hovering
		if (mousePos.x >= this->m_posRelativeToConsole.x && mousePos.x <= (this->m_posRelativeToConsole.x + this->m_size.x) - 1 && y1 == y2)
		{
			//check for click
			if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
			{
				this->m_bIsClicked = TRUE;
				return;
			}
			else
				this->m_bIsClicked = FALSE;
			this->m_bIsHovering = TRUE;
		}
		else
			this->m_bIsHovering = FALSE;
	}
	BOOL Button::IsClicked()
	{
		return this->m_bIsClicked;
	}
	BOOL Button::IsHovering()
	{
		return this->m_bIsHovering;
	}
}