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
#include <ConsoleWindow.hpp>

namespace ugr
{
    VOID ConsoleWindow::InitConsoleWindow()
    {
        //Store the memory address of the console we will then use it to display the buffer on the console window
        this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    VOID ConsoleWindow::CreateConsoleBufferWindow(Vector2i size, Vector2i fontSize)
    {
        //Create the buffer size here where we render graphics on
        this->m_buffer = new CharPixel[size.x * size.y]{};

        //Set the rect of the window
        this->m_rect = { 0, 0, SHORT(size.x - 1), SHORT(size.y - 1) };
        //Check if Console Window rect were applied if not terminate
        if (!SetConsoleWindowInfo(this->m_hConsole, TRUE, (PSMALL_RECT)&this->m_rect))
        {
            MessageBox(NULL, TEXT("Error"), TEXT("Could not set the size of the window"), MB_ICONERROR | MB_OK);
            exit(EXIT_FAILURE);
        }

        if (!SetConsoleScreenBufferSize(this->m_hConsole, { SHORT(this->m_screen.x), SHORT(this->m_screen.y) }))
            MessageBox(NULL, L"Couldn't set the console screen buffer size!", L"Error", MB_ICONERROR | MB_OK);
        
        SetConsoleActiveScreenBuffer(this->m_hConsole);

        SetConsoleMode(this->m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
        
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = NULL;
        cfi.dwFontSize.X = SHORT(fontSize.x);
        cfi.dwFontSize.Y = fontSize.y;
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL;

        wcscpy_s(cfi.FaceName, L"Consolas");
        SetCurrentConsoleFontEx(this->m_hConsole, FALSE, &cfi);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(this->m_hConsole, &csbi);
        if (this->m_screen.x > csbi.dwMaximumWindowSize.X)
        {
            MessageBox(NULL, L"Screen Width / Font Width To Large", L"Error", MB_OK | MB_ICONERROR);
        }
        if (this->m_screen.y > csbi.dwMaximumWindowSize.Y)
        {
            MessageBox(NULL, L"Screen Height / Font Height To Large", L"Error", MB_OK | MB_ICONERROR);
        }

        //Set the screen size
        this->m_screen = size;
        this->re.hConsole = this->m_hConsole;
        this->re.screen = this->m_screen;
        this->re.rect = this->m_rect;
        this->re.buffer = this->m_buffer;
        this->InitRenderTarget(re);
    }
    VOID ConsoleWindow::Display()
    {
        //Display the buffer on the Console Window
        WriteConsoleOutputW(this->m_hConsole, PCHAR_INFO(this->m_buffer), { SHORT(this->m_screen.x), SHORT(this->m_screen.y) }, {}, (PSMALL_RECT)&this->m_rect);
    }
}