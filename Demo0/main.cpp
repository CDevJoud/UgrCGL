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
#include <UgrCGL.hpp>
#include <memory>
using namespace ugr;

class Application : private ConsoleWindow
{
public:
	Application() :
		m_bIsRunning(TRUE),
		m_ptrPanel(new Panel),
		m_ptrInBox(new InputBox),
		m_ptrBox(new TextBox),
		m_ptrBtn(new Button)
	{
		this->InitConsoleWindow();
		this->CreateConsoleBufferWindow(Vector2i(240, 64), Vector2i(8, 16));

		this->m_ptrPanel->CreatePanel(Vector2i(40, 20));
		this->m_ptrPanel->SetPosition(Vector2i(100, 22));

		this->m_ptrInBox->CreateBox(Vector2i(38, 1));
		this->m_ptrInBox->SetPosition(Vector2i(1, 19));

		this->m_ptrBox->CreateBox(Vector2i(30, 15));
		this->m_ptrInBox->SetFlag(ENABLE_INPUT_ON_RETURN);

		this->m_ptrBtn->SetTitle(L"<Exit>", 0xC0);
		this->m_ptrBtn->SetColor(0x0C);
		this->m_ptrBtn->SetPosition(Vector2i(32, 1));
	}
	~Application()
	{
		this->ShutDown();
		delete this->m_ptrPanel;
		delete this->m_ptrInBox;
		delete this->m_ptrBox;
	}
	INT run()
	{
		while (this->m_bIsRunning)
		{
			this->ProcessEvents();
			this->m_ptrInBox->ProcessEvents(this);
			this->m_ptrPanel->ProcessEvents(this);
			this->m_ptrBtn->ProcessEvents(this);

			int a = m_ptrBox->GetLinesSize();
			int b = m_ptrBox->GetScrollPosition();
			if (this->Keyboard(VK_UP).bStrokeIsHeld && m_ptrBox->GetScrollPosition() > 0) this->m_ptrBox->MoveUp();
			if (this->Keyboard(VK_DOWN).bStrokeIsHeld && m_ptrBox->GetScrollPosition() < static_cast<int>(m_ptrBox->GetLinesSize()) - 12) this->m_ptrBox->MoveDown();
			if (this->Keyboard(VK_PRIOR).bStrokeIsHeld && m_ptrBox->GetScrollPosition() > 0) for (INT i = 0; i < 10; i++) this->m_ptrBox->MoveUp();
			if (this->Keyboard(VK_NEXT).bStrokeIsHeld && m_ptrBox->GetScrollPosition() < static_cast<int>(m_ptrBox->GetLinesSize() - 12)) for (INT i = 0; i < 10; i++) this->m_ptrBox->MoveDown();


			if (this->m_ptrInBox->Submited())
			{
				this->m_ptrBox->AddLine(this->m_ptrInBox->GetStrInputW());
				this->m_ptrInBox->ResetStrInput();
			}

			this->m_bIsRunning = !this->m_ptrBtn->IsClicked();

			this->ClearScreen();
			this->m_ptrPanel->ClearScreen(0x2588, 0x01);
			this->m_ptrPanel->RenderInputBox(this->m_ptrInBox);
			this->m_ptrPanel->RenderTextBox(this->m_ptrBox);
			this->m_ptrPanel->RenderButton(this->m_ptrBtn);
			this->m_ptrPanel->Display();
			this->RenderPanel(this->m_ptrPanel);
			this->Display();
		}
		this->ClearScreen();
		this->Display();
		return 0;
	}
private:
	InputBox* m_ptrInBox;
	Panel* m_ptrPanel;
	TextBox* m_ptrBox;
	Button* m_ptrBtn;
	BOOL m_bIsRunning;
};

int main(int argv, char** argc)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	return app->run();
}