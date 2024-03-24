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
#include <functional>
#include <map>

namespace ugr
{
	class Button::pImpl
	{
	public:
		pImpl()
		{

		}
		~pImpl()
		{

		}
		Vector2i m_size;
		LPCWSTR m_title;
		BYTE m_n8TitleColor;
		BYTE m_n8Color;
		Vector2i m_pos;
		Vector2i m_posRelativeToConsole;
		BOOL m_bIsClicked;
		BOOL m_bIsHovering;
		std::map<const char*, const std::function<void(void)>> m_mapFunctionCallBack;
	};

	Button::Button()
	{
		this->This = new pImpl;
	}

	Button::~Button()
	{
		delete this->This;
	}

	VOID Button::SetTitle(LPCWSTR t, BYTE col)
	{
		This->m_title = t;
		This->m_n8TitleColor = col;
		This->m_size.x = lstrlenW(t) + 2;
	}
	VOID Button::SetColor(BYTE color)
	{
		This->m_n8Color = color;
	}
	VOID Button::SetPosition(Vector2i pos)
	{
		This->m_pos = pos;
	}
	VOID Button::ProcessEvents(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos();
		INT y1 = mousePos.y - 1;
		INT y2 = This->m_posRelativeToConsole.y - 1;
		//Check for hovering
		if (mousePos.x >= This->m_posRelativeToConsole.x && mousePos.x <= (This->m_posRelativeToConsole.x + This->m_size.x) - 1 && y1 == y2)
		{
			if (This->m_mapFunctionCallBack["OnHovering"])
				This->m_mapFunctionCallBack["OnHovering"]();
			//check for click
			if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
			{
				This->m_bIsClicked = TRUE;
				if (This->m_mapFunctionCallBack["OnClicked"])
					This->m_mapFunctionCallBack["OnClicked"]();
				return;
			}
			else
				This->m_bIsClicked = FALSE;
			This->m_bIsHovering = TRUE;
		}
		else
		{
			This->m_bIsHovering = FALSE;
			if (This->m_mapFunctionCallBack["OnNotHovering"])
				This->m_mapFunctionCallBack["OnNotHovering"]();
		}
	}
	BOOL Button::IsClicked()
	{
		return This->m_bIsClicked;
	}
	VOID Button::OnClicked(const std::function<void(void)>& func)
	{
		This->m_mapFunctionCallBack.insert(std::pair<const char*, const std::function<void(void)>>("OnClicked", func));
	}
	VOID Button::OnHovering(const std::function<void(void)>& func)
	{
		This->m_mapFunctionCallBack.insert(std::pair<const char*, const std::function<void(void)>>("OnHovering", func));
	}
	VOID Button::OnNotHovering(const std::function<void(void)>& func)
	{
		This->m_mapFunctionCallBack.insert(std::pair<const char*, const std::function<void(void)>>("OnNotHovering", func));
	}
	BOOL Button::IsHovering()
	{
		return This->m_bIsHovering;
	}
	Vector2i Button::GetPosition() const
	{
		return This->m_pos;
	}
	Vector2i Button::GetSize() const
	{
		return This->m_size;
	}
	LPCWSTR Button::GetTitle() const
	{
		return This->m_title;
	}
	Color Button::GetTitleColor() const
	{
		return This->m_n8TitleColor;
	}
	Color Button::GetColor() const
	{
		return This->m_n8Color;
	}
	void Button::SetPositionRelativeToConsoleWindow(Vector2i pos)
	{
		This->m_posRelativeToConsole = pos;
	}
}