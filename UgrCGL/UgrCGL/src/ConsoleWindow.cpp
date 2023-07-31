#include "ConsoleWindow.hpp"

namespace ugr
{
    VOID ConsoleWindow::InitConsoleWindow()
    {
        //Store the memory address of the console we will then use it to display the buffer on the console window
        this->m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    VOID ConsoleWindow::CreateConsoleBufferWindow(COORD size)
    {
        //Create the buffer size here where we render graphics on
        this->m_buffer = new CHAR_INFO[size.X * size.Y]{};
        //Set the rect of the window
        this->m_rect = { 0, 0, SHORT(size.X - 1), SHORT(size.Y - 1) };
        //Check if Console Window rect were applied if not terminate
        if (!SetConsoleWindowInfo(this->m_hConsole, TRUE, &this->m_rect))
        {
            MessageBox(NULL, TEXT("Error"), TEXT("Could not set the size of the window"), MB_ICONERROR | MB_OK);
            exit(EXIT_FAILURE);
        }
        //Set the screen size
        this->m_screen = size;
    }
    VOID ConsoleWindow::Display()
    {
        //Display the buffer on the Console Window
        WriteConsoleOutputW(this->m_hConsole, this->m_buffer, this->m_screen, {}, &this->m_rect);
    }
}