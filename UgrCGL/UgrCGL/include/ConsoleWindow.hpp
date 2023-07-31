#pragma once
#include <Windows.h>
#include <Register.hpp>

namespace ugr
{
	class UGRCGL_API ConsoleWindow
	{
	public:
		/// <summary>
		/// This function will Init the ConsoleWindow by getting the memory address
		/// of the ConsoleWindow and store it for later use
		/// </summary>
		VOID InitConsoleWindow();
		/// <summary>
		/// This function will Create the Console buffer window with the specified size
		/// </summary>
		/// <param name="size"></param>
		VOID CreateConsoleBufferWindow(COORD size);

		/// <summary>
		/// This function will display the buffer to the Consolw Window
		/// </summary>
		VOID Display();
	private:
		HANDLE m_hConsole = NULL;
		CHAR_INFO* m_buffer = NULL;
		COORD m_screen = { 0 };
		SMALL_RECT m_rect = { 0 };
	};
}