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
#include <Panel.hpp>

namespace ugr
{
	/*! Class that is inherited using public inheritance
	* 
	* \class ConsoleWindow
	* \brief This class is the heart of the application, allowing you to configure your Console Window and perform Graphics on it.
	*
	* This class provides functionality to create and manage a console window for rendering graphics.
	*
	* **Usage Example:**
	* \code{.cpp}
	* #include <UgrCGL.hpp>
	*
	* class Demo : public ugr::ConsoleWindow
	* {
	* public:
	*     Demo()
	*     {
	*         this->InitConsoleWindow();
	*         this->CreateConsoleBufferWindow(ugr::Vector2i(240, 75), ugr::Vector2i(8, 14));
	*     }
	*
	*     int run()
	*     {
	*         while (true)
	*         {
	*			   this->ClearScreen();
	* 			   
	*			   //Render Function Here!
	* 
	*             this->Display();
	*         }
	*         return 0;
	*     }
	* };
	*
	* int main(int argc, char** argv)
	* {
	*     Demo d;
	*     return d.run();
	* }
	* \endcode
	*/
	class UGRCGL_API ConsoleWindow : public RenderTarget, public EventProcessor
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
		/// <summary>
		/// Releases all the memory that the class has stored.
		/// </summary>
		/// <remarks>
		/// Call this function once to release all the memory used by the class. 
		/// \note After calling this function, avoid invoking other functions, like RenderLine, SetPixel etc, 
		/// to prevent potential crashes in your program.
		/// </remarks>
		VOID ShutDown();
		FLOAT dt = 0.0F;
		VOID RenderPanel(Panel* panel);
		VOID ProcessFPS();
		FLOAT GetFPS() const;
		VOID SetFullScreen(BOOL sw);
	private:
		VOID SetUpFrame(Vector2i pos, Vector2i size, Color color);
		class pImpl;
		pImpl* m_pImpl = NULL;

		HANDLE m_hConsole = NULL;
		HANDLE m_hConsoleIn = NULL;
		PCharPixel m_buffer = NULL;
		Vector2i m_screen;
		ShortRect m_rect = { 0 };
		RenderElements re;
	};
}