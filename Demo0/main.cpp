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

void VertexShader(int& p, int& x, int& y)
{
	p += (p < 0) ? 4 * x++ + (600) : 4 * (x++ + y--) + 100;
}

class Demo : public ugr::ConsoleWindow
{
public:
	Demo()
	{
		this->InitConsoleWindow();
		this->CreateConsoleBufferWindow(ugr::Vector2i(240, 128), ugr::Vector2i(8, 8));
	}
	
	int run()
	{
		ugr::ShortRect rect1 = {10, 10, 5, 20};
		ugr::ShortRect rect2 = {20, 40, 40, 20};
		while (true)
		{
			this->ClearScreen();

			this->RenderCircle(ugr::Vector2i(120, 64), 20, 0x2588, 0x0F, VertexShader);
			this->RasterizeQuad(rect1, rect2);
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
