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
#include <UgrCGL.hpp>
#include <memory>
using namespace ugr;

class Application : private ConsoleWindow
{
public:
	Application() :
		m_bIsRunning(TRUE),
		m_ptrPanel(new Panel),
		m_ptrInBox(new InputBox)
	{
		this->InitConsoleWindow();
		this->CreateConsoleBufferWindow(Vector2i(240, 64), Vector2i(8, 16));

		this->m_ptrPanel->CreatePanel(Vector2i(40, 20));
		this->m_ptrPanel->SetPosition(Vector2i(100, 22));

		this->m_ptrInBox->CreateBox(Vector2i(38, 1));
		this->m_ptrInBox->SetPosition(Vector2i(1, 19));
	}
	~Application()
	{
		this->ShutDown();
		delete this->m_ptrPanel;
		delete this->m_ptrInBox;
	}
	INT run()
	{
		while (this->m_bIsRunning)
		{
			this->ProcessEvents();
			this->m_ptrInBox->ProcessEvents(this);
			this->m_ptrPanel->ProcessEvents(this);

			this->m_bIsRunning = !this->Keyboard(0x1B).bStrokeReleased;

			this->ClearScreen();
			this->m_ptrPanel->ClearScreen(0x2588, 0x01);
			this->m_ptrPanel->RenderInputBox(this->m_ptrInBox);
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
	BOOL m_bIsRunning;
};

int main(int argv, char** argc)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	return app->run();
}
