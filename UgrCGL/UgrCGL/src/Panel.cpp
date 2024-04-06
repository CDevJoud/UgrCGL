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
#include <Panel.hpp>
#include <vector>

namespace ugr
{
	BYTE SwitchByte(BYTE b)
	{
		BYTE rb = 0x00;
		BYTE high = (b & 0xF0) >> 4;
		BYTE low = (b & 0x0F) << 4;
		rb = high | low;
		return rb;
	}
	class Panel::pImpl
	{
	public:
		std::vector<MenuButtonProp> m_vecMenuButton;
		
		CharSurface m_n16BorderChar;
		Color m_n8BorderColor = 0x0F;
		
		Vector2i m_vecBufferSize;
		Vector2i m_vecPosition = Vector2i(1, 1);
		
		ScreenBuffer m_Buffer;
		RenderElements re;
		
		LPCWSTR m_Paneltitle = L"";
		SHORT m_PanelTitleColor;
		
		MenuBarProp m_MenuBarProp;
		
		BOOL m_bIsCloseable;
		BOOL m_bIsClosed;
	};
	
	VOID Panel::CreatePanel(Vector2i size)
	{
		this->m_pImpl = new pImpl;
		this->m_pImpl->m_vecBufferSize = size;
		this->m_pImpl->m_Buffer = new CharPixel[size.x * size.y];
		ZeroMemory(this->m_pImpl->m_Buffer, 4 * size.x * size.y);
		this->m_pImpl->re.buffer = this->m_pImpl->m_Buffer;
		this->m_pImpl->re.screen = size;
		this->m_pImpl->re.rect = { 0, 0, short(size.x), short(size.y) };
		this->m_pImpl->m_Paneltitle = L"";
		this->m_pImpl->m_bIsClosed = false;
		this->InitRenderTarget(m_pImpl->re);
	}
	
	VOID Panel::SetPosition(Vector2i pos)
	{
		this->m_pImpl->m_vecPosition = pos;
	}
	
	VOID Panel::SetBorderChar(CharSurface c)
	{
		this->m_pImpl->m_n16BorderChar = c;
	}
	VOID Panel::SetBorderColor(Color color)
	{
		this->m_pImpl->m_n8BorderColor = color;
	}
	
	VOID Panel::CreateMenuBar(BYTE sizex, CharSurface c, Color color)
	{
		this->m_pImpl->m_MenuBarProp.sizeX = sizex;
		this->m_pImpl->m_MenuBarProp.surface = c;
		this->m_pImpl->m_MenuBarProp.color = color;
	}
	
	VOID Panel::AddMenu(LPCWSTR menutitle, Menu* attachMenuto, SHORT col)
	{
		MenuButtonProp tmp;
		tmp.menuTitle = menutitle;
		tmp.RedirectMenuBox = attachMenuto;
		tmp.MenuButtonColor = col;
		this->m_pImpl->m_vecMenuButton.push_back(tmp);
	}
	
	//DANGEROUS function!!
	//This Function will be visited later due to wrong mouse reading coordinates & bugs a lot 
	//VOID Panel::RenderPanel(Panel* p)
	//{
	//    //Vector2i diff(1, 1);
	//    Vector2i p1(p->m_vecPosition);
	//    Vector2i p2((p->m_vecPosition + p->m_vecBufferSize));
	
	//    for (INT x = p1.x; x < p2.x; x++)
	//        for (INT y = p1.y; y < p2.y; y++)
	//        {
	//            INT py = (y - p1.y);
	//            INT px = (x - p1.x);
	//            auto surface = p->m_Buffer[py * p->m_vecBufferSize.x + px].Char.UnicodeChar;
	//            auto color = p->m_Buffer[py * p->m_vecBufferSize.x + px].Attributes;
	//            SetPixel(Vector2i(x, y), surface, color);
	//        }
	//    auto pos = p->m_vecPosition;
	//    auto size = p->m_vecBufferSize;
	//    auto color = p->m_n16BorderColor;
	//    auto title = p->m_Paneltitle;
	//    auto titlecol = p->m_PanelTitleColor;
	//    ////Draw The Border
	//    //this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x + size.x - 1, pos.y - 1), 0x2500, color);
	
	//    //this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x - 1, pos.y + size.y - 1), 0x2502, color);
	
	//    //this->RenderLine(Vector2i(pos.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y + size.y), 0x2500, color);
	
	//    //this->RenderLine(Vector2i(pos.x + size.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y), 0x2502, color);
	//    ////Set Corner style
	//    ////Top
	//    //SetPixel(Vector2i(pos.x - 1, pos.y - 1), 0x256D, color);
	
	//    ////Right
	//    //SetPixel(Vector2i(pos.x + size.x, pos.y - 1), 0x256E, color);
	
	//    ////Left
	//    //SetPixel(Vector2i(pos.x - 1, pos.y + size.y), 0x2570, color);
	
	//    ////Bottom
	//    //SetPixel(pos + size, 0x256F, color);
	
	//    this->RenderText(Vector2i(pos.x + (size.x / 2) - (lstrlenW(title) / 2), pos.y - 1), title, titlecol);
	//}
	
	VOID Panel::RenderTextBox(TextBox* box)
	{
		auto pos = box->GetPosition();
		auto size = box->GetSize();
		
		Vector2i p1 = pos;
		Vector2i p2 = pos + size;
		
		box->RenderSilent();
		for (INT y = p1.y; y < p2.y; y++)
		    for (INT x = p1.x; x < p2.x; x++)
		    {
		        INT py = (y - p1.y);
		        INT px = (x - p1.x);
		        auto surface = box->GetCharPixel(py * box->GetSize().x + px).Char.UnicodeChar;
		        auto color = box->GetCharPixel(py * box->GetSize().x + px).Color;
		        SetPixel(Vector2i(x, y), surface, color);
		    }
		// Calculate and draw the scroll bar thumb
		float fThumbHeight = static_cast<float>(box->GetVisibileHeight()) / box->GetLinesSize() * box->GetScrollBarHeight();
		int nThumbY = static_cast<int>(static_cast<float>(box->GetScrollPosition()) / (box->GetLinesSize() - box->GetVisibileHeight()) * (box->GetScrollBarHeight() - fThumbHeight));
		
		//Old But Gold
		////Draw Arrow
		//this->SetPixel(Vector2i(pos.x + box->m_scrollbarPosition.x, pos.y + box->m_scrollbarPosition.y - 1), 0x2191);
		
		//// Draw the scroll bar background
		//for (int y = 0; y < box->m_nScrollBarHeight; y++)
		//{
		//    //Draw Arrow
		//    this->SetPixel(Vector2i(pos.x + box->m_scrollbarPosition.x, pos.y + box->m_scrollbarPosition.y + y + 1), 0x2193);
		//    this->SetPixel(Vector2i(box->m_scrollbarPosition.x + pos.x, box->m_scrollbarPosition.y + y + pos.y));
		//}
		
		// Draw the scroll bar thumb
		
		//before drawing check if the thumb height is bigger than the Visibile height
		//if the thumb height larger than the visibile set it to the visibile height
		//else check if the thumb height is lower than 1.0f, if so return alpha true.
		this->SetUpFrame(pos, size, 0x0F);
		fThumbHeight = (fThumbHeight >= box->GetVisibileHeight()) ? box->GetVisibileHeight() : (fThumbHeight < 1.0f) ? 1.0f : fThumbHeight;
		
		for (int y = 0; y < static_cast<int>(fThumbHeight); y++)
		{
		    this->SetPixel(Vector2i(box->GetScrollBarPosition().x + pos.x, box->GetScrollBarPosition().y + nThumbY + y + pos.y), 0x2588, 0x06);
		}
		
	}
	
	VOID Panel::RenderInputBox(InputBox* box)
	{
		auto pos = box->GetPosition();
		auto size = box->GetSize();
		auto title = box->GetTitle();
		auto titlecol = box->GetTitleColor();
		auto color = box->GetBorderColor();
		box->SetPositionRelativeToConsoleWindow(this->m_pImpl->m_vecPosition + pos);
		
		Vector2i p1 = pos;
		Vector2i p2 = pos + size;
		box->RenderSilent();
		for (INT y = p1.y; y < p2.y; y++)
		    for (INT x = p1.x; x < p2.x; x++)
		    {
		        INT py = (y - p1.y);
		        INT px = (x - p1.x);
		        auto surface = box->GetCharPixel(py * box->GetSize().x + px).Char.UnicodeChar;
		        auto color = box->GetCharPixel(py * box->GetSize().x + px).Color;
		        SetPixel(Vector2i(x, y), surface, color);
		    }
		
		
		this->SetUpFrame(pos, size, color);
		this->RenderText(Vector2i(pos.x + 2, pos.y - 1), title, titlecol);
	}
	
	//Glitch on Rendering Text if it's far next to Panel frame!
	VOID Panel::RenderButton(Button* btn)
	{
		auto pos = btn->GetPosition();
		auto size = btn->GetSize();
		auto title = btn->GetTitle();
		auto titlecol = btn->GetTitleColor();
		auto color = btn->GetColor();
		if (btn->IsHovering())
		{
		    color = ~color;
		    titlecol = ~titlecol;
		}
		
		
		btn->SetPositionRelativeToConsoleWindow(this->m_pImpl->m_vecPosition + pos);
		
		this->RenderLine(pos, Vector2i(pos.x + size.x - 1, pos.y + size.y), 0x2588, color);
		this->RenderText(Vector2i(pos.x + (size.x / 2) - (lstrlenW(title) / 2), pos.y), title, titlecol);
		//this->RenderText(Vector2i(1, 1), title, titlecol);
	}
	
	VOID Panel::SetTitle(LPCWSTR title, Color color)
	{
		this->m_pImpl->m_Paneltitle = title;
		this->m_pImpl->m_PanelTitleColor = color;
	}
	VOID Panel::Display()
	{
		auto display = [&]() mutable->void {
		    void* __ptr64 hConsole = m_pImpl->re.hConsole;
		    ScreenBuffer buffer = m_pImpl->re.buffer;
		    Vector2i ScreenSize = m_pImpl->re.screen;
		    ShortRect rect = m_pImpl->re.rect;
		    WriteConsoleOutputW(GetStdHandle(STD_OUTPUT_HANDLE), reinterpret_cast<PCHAR_INFO>(buffer), {SHORT(ScreenSize.x), SHORT(ScreenSize.y)}, {}, reinterpret_cast<PSMALL_RECT>(&rect));
		    };
		//RenderMenuBar
		auto menusizex = this->m_pImpl->m_MenuBarProp.sizeX;
		auto menusur = this->m_pImpl->m_MenuBarProp.surface;
		auto menucol = this->m_pImpl->m_MenuBarProp.color;
		
		if(menusizex > 0)
		    this->RenderLine(Vector2i(0, 0), Vector2i(menusizex, 0), menusur, menucol);
		
		SHORT offsetX = 2;
		for (auto& i : this->m_pImpl->m_vecMenuButton)
		{
		    //This is temp
		    i.RedirectMenuBox->SetClickablePosition(Vector2i(offsetX, 0));
		    //----------------------------------------------------------------
		
		    this->RenderText(Vector2i(offsetX, 0), i.menuTitle, i.MenuButtonColor);
		    offsetX += lstrlenW(i.menuTitle) + 2;
		    
		
		    //Render the Menu
		    if (i.RedirectMenuBox->IsHidden())
		    {
		        Vector2i offset(0, 1);
		        ShortRect rect;
		        rect.x = i.RedirectMenuBox->GetClickablePosition().x + offset.x;
		        rect.y = i.RedirectMenuBox->GetClickablePosition().y + offset.y;
		
		        rect.width = i.RedirectMenuBox->GetSize().x;
		        rect.height = i.RedirectMenuBox->GetSize().y;
		
		        this->RasterizeQuad(rect, 0x2588, i.RedirectMenuBox->GetColor() & 0x0F);
		        Vector2i elOffset = i.RedirectMenuBox->GetClickablePosition() + offset;
		        
		        //Render Menu Elements
		        VMP VectorMenuPair = i.RedirectMenuBox->GetElements();
		        
		        for (int j = 0; j < VectorMenuPair.size; j++)
		        {
		            this->RenderText(elOffset, VectorMenuPair.dStrW[j], SwitchByte(i.RedirectMenuBox->GetColor()));
		            elOffset.y++;
		        }
		        i.RedirectMenuBox->FreeVMPGetter(VectorMenuPair);
		    }
		}
	}
	VOID Panel::ProcessEvents(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos() - this->m_pImpl->m_vecPosition;
		for (auto& i : this->m_pImpl->m_vecMenuButton)
		{
		    auto pos = i.RedirectMenuBox->GetClickablePosition();
		    auto mSize = i.RedirectMenuBox->GetSize();
		    SHORT size = lstrlenW(i.menuTitle) + 1;
		    if (mousePos.x >= pos.x && mousePos.x <= (pos.x + lstrlenW(i.menuTitle) - 1) && mousePos.y == pos.y)
		    {
		        if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
		        {
		            i.RedirectMenuBox->SetVisibility(true);
		        }
		    }
		    else if (this->CheckInBoundaries(Vector2i(mousePos.x, mousePos.y - 1), { 0, 0, short(mSize.x), short(mSize.y) }) && i.RedirectMenuBox->IsHidden())
		    {
		        if(EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
		        {
		            i.RedirectMenuBox->SetMenuValueOnPressed(mousePos.y - 1);
		            i.RedirectMenuBox->CallLambdaFunction("OnElementPressed");
		        }
		    }
		    //check for Mouse hovering on the menu
		    else if (!(mousePos.x >= pos.x && mousePos.x < (pos.x + mSize.x) &&
		        mousePos.y >= pos.y + 1 && mousePos.y < (pos.y + mSize.y + 1)))
		        i.RedirectMenuBox->SetVisibility(false);
		}
	}
	VOID Panel::SetUpFrame(Vector2i pos, Vector2i size, Color color)
	{
		this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x + size.x - 1, pos.y - 1), 0x2500, color);
		
		this->RenderLine(Vector2i(pos.x - 1, pos.y - 1), Vector2i(pos.x - 1, pos.y + size.y - 1), 0x2502, color);
		
		this->RenderLine(Vector2i(pos.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y + size.y), 0x2500, color);
		
		this->RenderLine(Vector2i(pos.x + size.x, pos.y + size.y), Vector2i(pos.x + size.x, pos.y), 0x2502, color);
		
		SetPixel(Vector2i(pos.x - 1, pos.y - 1), 0x256D, color);
		
		//Right
		SetPixel(Vector2i(pos.x + size.x, pos.y - 1), 0x256E, color);
		
		//Left
		SetPixel(Vector2i(pos.x - 1, pos.y + size.y), 0x2570, color);
		
		//Bottom
		SetPixel(pos + size, 0x256F, color);
		
		
	}
	
	BOOL Panel::IsCloseable() const
	{
		return this->m_pImpl->m_bIsCloseable;
	}
	
	VOID Panel::SetCloseability(BOOL value)
	{
		this->m_pImpl->m_bIsCloseable = value;
	}
	
	VOID Panel::Close(BOOL value)
	{
		this->m_pImpl->m_bIsClosed = value;
	}
	
	BOOL Panel::IsClosed() const
	{
		return this->m_pImpl->m_bIsClosed;
	}
	
	/////////////////////PIMPLE GETTERS!/////////////////////
	
	Vector2i Panel::GetVecPosition() const
	{
		return this->m_pImpl->m_vecPosition;
	}
	Vector2i Panel::GetVecBufferSize() const
	{
		return this->m_pImpl->m_vecBufferSize;
	}
	Color Panel::GetBorderColor() const
	{
		return this->m_pImpl->m_n8BorderColor;
	}
	LPCWSTR Panel::GetPanelTitle() const
	{
		return this->m_pImpl->m_Paneltitle;
	}
	Color Panel::GetPanelTitleColor() const
	{
		return this->m_pImpl->m_PanelTitleColor;
	}
	ScreenBuffer Panel::GetBuffer() const
	{
		return m_pImpl->m_Buffer;
	}
}