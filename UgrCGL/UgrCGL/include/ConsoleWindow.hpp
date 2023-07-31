#pragma once
#include <Windows.h>
#include <Register.hpp>

namespace ugr
{
	class UGRCGL_API ConsoleWindow
	{
	public:
		/// <summary>
		/// Initializes the ConsoleWindow by retrievingand storing its memory address for future use.
		///	This function ensures seamless interaction with the ConsoleWindow throughout the application's lifecycle.
		///	By obtaining the memory address, we enable efficient access to the ConsoleWindow's properties and data.
		///	Feel free to call this function at the beginning of your application to set up the ConsoleWindow environment.
		/// </summary>
		VOID InitConsoleWindow();
		/// <summary>
		/// Creates a new Console buffer window with the specified size.
		/// </summary>
		/// <param name="size">The desired size of the Console buffer window.</param>
		/// <remarks>
		/// Use this function to create a customized Console buffer window with the provided size.
		/// This allows for a more tailored and interactive user experience within the Console environment.
		/// </remarks>
		VOID CreateConsoleBufferWindow(COORD size);
		/// <summary>
		/// Displays the buffer content in the Console Window.
		/// </summary>
		/// <remarks>
		/// Use this function to render and present the contents of the buffer on the Console Window.
		/// Once called, the updated buffer content will be visible to the user in the Console interface.
		/// </remarks>
		VOID Display();
	private:
		HANDLE m_hConsole = NULL;
		CHAR_INFO* m_buffer = NULL;
		COORD m_screen = { 0 };
		SMALL_RECT m_rect = { 0 };
	};
}