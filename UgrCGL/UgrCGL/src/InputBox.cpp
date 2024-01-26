#include <Windows.h>
#include <InputBox.hpp>
#include <string>
#include <conio.h>

namespace ugr
{
	class InputBox::pImpl
	{
	public:
		~pImpl();
		Vector2i m_size;
		Vector2i m_pos;
		Vector2i m_posRelativeToConsole;
		RenderElements re;
		BOOL m_bEnableInput = FALSE;
		BOOL m_bHasSumbited = FALSE;
		LPCWSTR m_title;
		Color m_n8TitleColor;
		Color m_n8ColorBorder = 0x08;
		CGLFlags m_flags;
		
		std::wstring m_strInput;
		VOID ProcessKeyInput();
		VOID CleanStrFromJunk(std::wstring& str);
	};
	InputBox::InputBox()
	{
		this->This = new pImpl;
	}
	InputBox::~InputBox()
	{
		delete This;
	}
	VOID InputBox::CreateBox(Vector2i size)
	{
		This->m_size = size;
		This->re.screen = size;
		This->re.rect = { 0, 0, SHORT(size.x), SHORT(size.y) };
		This->re.buffer = new CharPixel[size.x * size.y]{};
		this->InitRenderTarget(This->re);
	}
	VOID InputBox::SetPosition(Vector2i pos)
	{
		This->m_pos = pos;
	}
	VOID InputBox::Clean()
	{
		delete This->re.buffer;
		delete This;
	}
	VOID InputBox::ProcessEvents(EventProcessor* EP)
	{
		auto mousePos = EP->GetMousePos();
		INT y1 = mousePos.y - 1;
		INT y2 = This->m_posRelativeToConsole.y - 1;
		if (mousePos.x >= This->m_posRelativeToConsole.x && mousePos.x <= (This->m_posRelativeToConsole.x + This->m_size.x) - 1 &&
			mousePos.y >= This->m_posRelativeToConsole.y && mousePos.y <= (This->m_posRelativeToConsole.y + This->m_size.y) - 1)
		{
			if (EP->Mouse(EventProcessor::MouseType::Left).bStrokePressed)
			{
				This->m_bEnableInput = TRUE;
				This->m_n8ColorBorder = 0x0F;
				return;
			}
		}
		if (This->m_bEnableInput)
			This->ProcessKeyInput();
		else
			This->m_bHasSumbited = FALSE;
	}
	LPCWSTR InputBox::GetStrInputW() const
	{
		return This->m_strInput.c_str();
	}
	LPCSTR InputBox::GetStrInput() const
	{
		INT sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, This->m_strInput.c_str(), -1, NULL, 0, NULL, NULL);
		std::string str(sizeNeeded, 0);
		WideCharToMultiByte(CP_UTF8, 0, This->m_strInput.c_str(), -1, &str[0], sizeNeeded, NULL, NULL);
		return str.c_str();
	}
	VOID InputBox::SetStrInput(LPCWSTR str)
	{
		This->m_strInput = str;
	}
	VOID InputBox::ResetStrInput()
	{
		This->m_strInput = L"";
	}
	BOOL InputBox::IsFocused() const
	{
		return This->m_bEnableInput;
	}
	BOOL InputBox::Submited()
	{
		return This->m_bHasSumbited;
	}
	VOID InputBox::SetFlag(CGLFlags flag)
	{
		This->m_flags = flag;
	}
	VOID InputBox::SetTitle(LPCWSTR title, Color col)
	{
		This->m_title = title;
		This->m_n8TitleColor = col;
	}
	VOID InputBox::RenderSilent()
	{
		this->ClearScreen();
		this->RenderText(Vector2i(0, 0), This->m_strInput.c_str());
	}
	Vector2i InputBox::GetPosition() const
	{
		return This->m_pos;
	}
	Vector2i InputBox::GetSize() const
	{
		return This->m_size;
	}
	LPCWSTR InputBox::GetTitle() const
	{
		return This->m_title;
	}
	Color InputBox::GetTitleColor() const
	{
		return This->m_n8TitleColor;
	}
	Color InputBox::GetBorderColor() const
	{
		return This->m_n8ColorBorder;
	}
	VOID InputBox::SetPositionRelativeToConsoleWindow(Vector2i pos)
	{
		This->m_posRelativeToConsole = pos;
	}
	InputBox::pImpl::~pImpl()
	{
		delete[] this->re.buffer;
	}
	VOID InputBox::pImpl::ProcessKeyInput()
	{
		//Process Key Might be Improved in the future!
		SHORT c = _getch();
		if (c == 0x08 && !this->m_strInput.empty())
		{
			this->m_strInput.pop_back();
			this->m_strInput.shrink_to_fit();
		}
		if (c != NULL)
			this->m_strInput.push_back(c);
		if (c == 0x1B)
		{
			this->m_bEnableInput = FALSE;
			this->m_n8ColorBorder = 0x08;
			this->m_strInput = L"";
		}
		//This will be changed!!
		if (c == 0x0D && this->m_flags == 1)
		{
			this->m_bHasSumbited = TRUE;
			this->m_n8ColorBorder = 0x0F;
		}
		else if (c == 0x0D)
		{
			this->m_bHasSumbited = TRUE;
			this->m_bEnableInput = FALSE;
			this->m_n8ColorBorder = 0x08;
		}
		else
			this->m_bHasSumbited = FALSE;
		if (c == 0x7F)
		{
			this->m_strInput.clear();
			this->m_strInput.shrink_to_fit();
		}
		//Handling Arrow key
		//_getch will return two keycodes for arrow keys the first keycode 224 to identify that is an arrow key were pressed
		//and the second keycode shows the which arrow and by calling another _getch we can skip that second keycode
		if (c == 224)
			_getch();
		this->CleanStrFromJunk(this->m_strInput);
	}
	VOID InputBox::pImpl::CleanStrFromJunk(std::wstring& str)
	{
		std::wstring tmp;
		for (auto& i : str)
			if (i != 0x08 && i != 0x01 && i != 0x0D && i != 0x1B && i != 0xE0)
				tmp.push_back(i);
		str = tmp;
	}
	CharPixel InputBox::GetCharPixel(INT val) const
	{
		return This->re.buffer[val];
	}
}
