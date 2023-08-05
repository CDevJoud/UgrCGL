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
#include <Menu.hpp>
#include <vector>

namespace ugr
{
	class Menu::pImpl
	{
	public:
		SHORT m_n16Color = 0x08;
		BOOL m_bIsHidden = TRUE;
		std::vector<LPCWSTR> m_vecElements;
		Vector2i m_ClickableMenuPosition;
		Vector2i m_size;
	};
	Menu::~Menu()
	{
		this->m_pImpl->m_vecElements.clear();
		this->m_pImpl->m_vecElements.shrink_to_fit();
		delete this->m_pImpl;
	}
	VOID Menu::CreateMenu(Vector2i size)
	{
		this->m_pImpl = new pImpl;
		this->m_pImpl->m_size = size;
	}
	VOID Menu::AddElements(LPCWSTR str)
	{
		this->m_pImpl->m_vecElements.push_back(str);
	}
	VOID Menu::SetColor(SHORT color)
	{
		this->m_pImpl->m_n16Color = color;
	}
}