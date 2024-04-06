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
#include <Panel.hpp>
#include <chrono>

namespace ugr
{
    class ConsoleWindow::pImpl
    {
    public:
        std::chrono::system_clock::time_point tp1 = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point tp2 = std::chrono::system_clock::now();
    };
    VOID ConsoleWindow::InitConsoleWindow()
    {
        //Store the memory address of the console we will then use it to display the buffer on the console window
        this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        this->m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
        this->m_pImpl = new pImpl;
    }
    VOID ConsoleWindow::CreateConsoleBufferWindow(Vector2i size, Vector2i fontSize)
    {
        //Check if handleConsole is init
        if (!this->m_hConsole)
            MessageBox(NULL, L"Bad Handle", L"Error", MB_ICONERROR | MB_OK);

        //Set screen size relative to the given parameter
        this->m_screen = size;

        this->m_rect = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(this->m_hConsole, TRUE, (PSMALL_RECT)&this->m_rect);

        if (!SetConsoleScreenBufferSize(this->m_hConsole, { SHORT(this->m_screen.x), SHORT(this->m_screen.y) }))
            MessageBox(NULL, L"Couldn't set the console screen buffer size!", L"Error", MB_ICONERROR | MB_OK);

        SetConsoleActiveScreenBuffer(this->m_hConsole);

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

        this->m_rect.x = 0;
        this->m_rect.y = 0;
        this->m_rect.width = this->m_screen.x - 1;
        this->m_rect.height = this->m_screen.y - 1;

        SetConsoleWindowInfo(this->m_hConsole, TRUE, (PSMALL_RECT)&this->m_rect);

        SetConsoleMode(this->m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

        this->m_buffer = new CharPixel[this->m_screen.x * this->m_screen.y];
        ZeroMemory(this->m_buffer, sizeof(CharPixel) * SHORT(this->m_screen.x) * SHORT(this->m_screen.y));

        //Init RenderElements and Renderer
        re.buffer = this->m_buffer;
        re.hConsole = this->m_hConsole;
        re.rect = this->m_rect;
        re.screen = this->m_screen;
        this->InitRenderTarget(re);
        this->InitEventProcessor(this->m_hConsoleIn);
    }
    VOID ConsoleWindow::Display()
    {
        //Display the buffer on the Console Window
        WriteConsoleOutputW(this->m_hConsole, PCHAR_INFO(this->m_buffer), { SHORT(this->m_screen.x), SHORT(this->m_screen.y) }, {}, (PSMALL_RECT)&this->m_rect);
    }
    VOID ConsoleWindow::ShutDown()
    {
        CloseHandle(this->m_hConsole);
        CloseHandle(this->m_hConsoleIn);
        delete[] this->m_buffer;
        delete m_pImpl;
    }
    VOID ConsoleWindow::RenderPanel(Panel* panel)
    {
        Vector2i p1(panel->GetVecPosition());
        Vector2i mpos, msize;
        mpos = panel->GetVecPosition();
        msize = panel->GetVecBufferSize();
        Vector2i p2( mpos + msize);
        auto pos = panel->GetVecPosition();
        auto size = panel->GetVecBufferSize();
        auto color = panel->GetBorderColor();
        auto title = panel->GetPanelTitle();
        auto titlecol = panel->GetPanelTitleColor();
        //Draw The Border
        
        if (!panel->IsClosed())
        {
            SetUpFrame(pos, size, color);
            this->RenderText(Vector2i(pos.x + (size.x / 2) - (lstrlenW(title) / 2), pos.y - 1), title, titlecol);

            for (INT y = p1.y; y < p2.y; y++)
                for (INT x = p1.x; x < p2.x; x++)
                {
                    INT py = (y - p1.y);
                    INT px = (x - p1.x);
                    auto surface = panel->GetBuffer()[py * panel->GetVecBufferSize().x + px].Char.UnicodeChar;
                    auto _color = panel->GetBuffer()[py * panel->GetVecBufferSize().x + px].Color;
                    SetPixel(Vector2i(x, y), surface, _color);
                }
            /*Panel::pImpl* s = NULL;*/
        }
        if (panel->IsCloseable() && !panel->IsClosed())
        {
            Vector2i newPos = { pos.x + (size.x - 4), pos.y - 1 };
            ShortRect rect = { newPos.x, newPos.y, (SHORT)newPos.x + 3, newPos.y + 1 };
            if (this->CheckInBoundaries(this->GetMousePos(), rect))
            {
                this->RenderText(newPos, L"{X}", ~0xCF);
                if (this->Mouse(EventProcessor::MouseType::Left).bStrokeReleased)
                    panel->Close(true);
            }
            else 
                this->RenderText(newPos, L"{X}", 0xCF);
            
            //this->Display();
        }
    }
    VOID ConsoleWindow::ProcessFPS()
    {
        this->m_pImpl->tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> dt = this->m_pImpl->tp2 - this->m_pImpl->tp1;
        this->m_pImpl->tp1 = this->m_pImpl->tp2;
        this->dt = dt.count();
    }
    FLOAT ConsoleWindow::GetFPS() const
    {
        return 1.0f / this->dt;
    }
    VOID ConsoleWindow::SetFullScreen(BOOL sw)
    {
        if (sw)
        {
            HWND consoleWindow = GetConsoleWindow();
            if (consoleWindow != NULL)
            {
                SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLongPtr(consoleWindow, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(consoleWindow, NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
            }
        }
        else
        {
            HWND consoleWindow = GetConsoleWindow();
            if (consoleWindow != NULL)
            {
                SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLongPtr(consoleWindow, GWL_STYLE) | WS_OVERLAPPEDWINDOW);
                SetConsoleWindowInfo(&this->m_hConsole, TRUE, (PSMALL_RECT)&this->m_rect);
            }
        }
    }
    VOID ConsoleWindow::SetUpFrame(Vector2i pos, Vector2i size, Color color)
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
}