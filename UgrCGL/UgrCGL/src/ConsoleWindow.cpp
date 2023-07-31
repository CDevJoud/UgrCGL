#include <Windows.h>
#include <ConsoleWindow.hpp>

namespace ugr
{
    VOID ConsoleWindow::InitConsoleWindow()
    {
        //Store the memory address of the console we will then use it to display the buffer on the console window
        this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    VOID ConsoleWindow::CreateConsoleBufferWindow(Vector2i size)
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