﻿// O------------------------------------LICENSE--------------------------------------O
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

class Demo : private ugr::ConsoleWindow
{
public:
	int run()
	{
		this->InitConsoleWindow();
		this->CreateConsoleBufferWindow(ugr::Vector2i(240, 128), ugr::Vector2i(8, 8));
		ugr::Panel p;
		p.CreatePanel(ugr::Vector2i(40, 40));
		p.SetPosition(ugr::Vector2i(120 - 20, 64 - 20));
		p.CreateMenuBar(39, 0x2588, 0x08);
		while (true)
		{
			p.ClearScreen(0x2588, 0x01);

			p.Display();

			this->ClearScreen(0x2588, 0x0C);
			this->RenderPanel(&p);
			this->Display();
		}
		return 0;
	}
};

int main()
{
	Demo d;
	return d.run();
}
