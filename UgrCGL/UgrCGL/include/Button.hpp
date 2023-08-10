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
#include <EventProcessor.hpp>
#include <Vector.hpp>

namespace ugr
{
	class UGRCGL_API Button
	{
	public:
		/// <summary>
		/// Sets the title and title color of the button.
		/// </summary>
		/// <param name="title">The text to display on the button.</param>
		/// <param name="color">The title color of the button.</param>
		VOID SetTitle(LPCWSTR title, BYTE color);
		/// <summary>
		/// Set The Button Color.
		/// </summary>
		/// <param name="color"></param>
		VOID SetColor(BYTE color);
		/// <summary>
		/// Set position of the button.
		/// </summary>
		/// <param name="pos"></param>
		VOID SetPosition(Vector2i pos);
		/// <summary>
		/// Processes events for the button, such as handling hover and click actions.
		/// </summary>
		/// <param name="EP">A pointer to the EventProcessor responsible for handling events.</param>
		VOID ProcessEvents(EventProcessor* EP);
		/// <summary>
		/// Check if the button were clicked.
		/// </summary>
		/// <returns></returns>
		BOOL IsClicked();
		/// <summary>
		/// Check if the mouse hovers on the button.
		/// </summary>
		/// <returns></returns>
		BOOL IsHovering();
	private:
		friend class Panel;
		Vector2i m_size;
		LPCWSTR m_title;
		BYTE m_n8TitleColor;
		BYTE m_n8Color;
		Vector2i m_pos;
		Vector2i m_posRelativeToConsole;
		BOOL m_bIsClicked;
		BOOL m_bIsHovering;
	};
}