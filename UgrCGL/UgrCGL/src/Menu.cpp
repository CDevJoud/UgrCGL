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
#include <Menu.hpp>
#include <vector>
#include <map>

namespace ugr
{
	class Menu::pImpl
	{
	public:
		Color m_n8Color = 0x08;
		BOOL m_bIsHidden = TRUE;
		std::vector<LPCWSTR> m_vecElements;
		Vector2i m_ClickableMenuPosition;
		Vector2i m_Size;
		SHORT m_n16MenuPressed;

		std::map<const char*, const std::function<void(int)>> m_mapFunctionCallBack;
	};
	Menu::Menu()
	{
		this->This = new pImpl;
	}
	Menu::~Menu()
	{
		This->m_vecElements.clear();
		This->m_vecElements.shrink_to_fit();
		delete this->This;
	}
	VOID Menu::CreateMenu(SHORT x)
	{
		if(!this->This)
			this->This = new pImpl;
		This->m_Size.x = x;
	}
	VOID Menu::AddElements(LPCWSTR str)
	{
		This->m_vecElements.push_back(str);
	}
	VOID Menu::SetColor(SHORT color)
	{
		This->m_n8Color = color;
	}
	VOID Menu::SetClickablePosition(Vector2i pos)
	{
		This->m_ClickableMenuPosition = pos;
	}
	VOID Menu::SetVisibility(BOOL sw)
	{
		This->m_bIsHidden = sw;
	}
	VOID Menu::OnMenuElementPressed(const std::function<void(int)>& func)
	{
		This->m_mapFunctionCallBack.insert(std::pair<const char*, const std::function<void(int)>>("OnElementPressed", func));
	}
	Color Menu::GetColor() const
	{
		return This->m_n8Color;
	}
	BOOL Menu::IsHidden() const
	{
		return This->m_bIsHidden;
	}
	Vector2i Menu::GetSize() const
	{
		This->m_Size.y = This->m_vecElements.size();
		return This->m_Size;
	}
	Vector2i Menu::GetClickablePosition() const
	{
		return This->m_ClickableMenuPosition;
	}
	VMP Menu::GetElements() const
	{
		VMP p;
		p.size = This->m_vecElements.size();

		p.dStrW = new wchar_t*[p.size];
		for (std::size_t i = 0; i < p.size; ++i)
		{
			p.dStrW[i] = new wchar_t[lstrlenW(This->m_vecElements[i]) + 1];
			lstrcpyW(p.dStrW[i], This->m_vecElements[i]);
		}
		return p;
	}
	VOID Menu::FreeVMPGetter(VMP vmp)
	{
		for (size_t i = 0; i < vmp.size; ++i) {
			delete[] vmp.dStrW[i];
		}
		delete[] vmp.dStrW;
	}
	VOID Menu::SetMenuValueOnPressed(INT value)
	{
		This->m_n16MenuPressed = value;
	}
	VOID Menu::CallLambdaFunction(LPCSTR func)
	{
		if (!strcmp(func, "OnElementPressed"))
		{
			if (This->m_mapFunctionCallBack[func])
				This->m_mapFunctionCallBack[func](This->m_n16MenuPressed);
		}
	}
}