#pragma once
#include <RenderTarget.hpp>

namespace ugr
{
	class UGRCGL_API ConsoleWindow : public RenderTarget
	{
	public:
		/// <summary>
		/// Initializes the ConsoleWindow by retrieving and storing its memory address for future use.
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
		VOID CreateConsoleBufferWindow(Vector2i size);
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
		PCharPixel m_buffer = NULL;
		Vector2i m_screen;
		ShortRect m_rect = { 0 };
		RenderElements re;
	};
}