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
		VOID CreateConsoleBufferWindow(Vector2i size, Vector2i fontSize);
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
		HANDLE m_hConsoleIn = NULL;
		PCharPixel m_buffer = NULL;
		Vector2i m_screen;
		ShortRect m_rect = { 0 };
		RenderElements re;
	};
}