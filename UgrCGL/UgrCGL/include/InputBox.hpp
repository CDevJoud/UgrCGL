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
#include <EventProcessor.hpp>

namespace ugr
{
    class UGRCGL_API InputBox : private RenderTarget
    {
    public:
        /// <summary>
        /// Default constructor for the InputBox class.
        /// </summary>
        InputBox();

        /// <summary>
        /// Destructor for the InputBox class.
        /// </summary>
        ~InputBox();

        /// <summary>
        /// Creates an input box with the specified size.
        /// </summary>
        /// <param name="size">The size of the input box.</param>
        VOID CreateBox(Vector2i size);

        /// <summary>
        /// Sets the position of the input box.
        /// </summary>
        /// <param name="pos">The position to set.</param>
        VOID SetPosition(Vector2i pos);

        /// <summary>
        /// Clears the content of the input box.
        /// </summary>
        VOID Clean();

        /// <summary>
        /// Processes events for the input box using the provided EventProcessor.
        /// </summary>
        /// <param name="EP">The EventProcessor instance to use for event handling.</param>
        VOID ProcessEvents(EventProcessor* EP);

        /// <summary>
        /// Returns the input string as a wide character string (LPCWSTR).
        /// </summary>
        /// <returns>The input string as a wide character string.</returns>
        LPCWSTR GetStrInputW() const;

        /// <summary>
        /// Returns the input string as a narrow character string (LPCSTR).
        /// </summary>
        /// <returns>The input string as a narrow character string.</returns>
        LPCSTR GetStrInput() const;

        /// <summary>
        /// Sets the input string using a wide character string.
        /// </summary>
        /// <param name="str">The wide character string to set as input.</param>
        VOID SetStrInput(LPCWSTR str);

        /// <summary>
        /// Resets the input string to an empty state.
        /// </summary>
        VOID ResetStrInput();

        /// <summary>
        /// Checks if the input box is currently focused.
        /// </summary>
        /// <returns>TRUE if the input box is focused, FALSE otherwise.</returns>
        BOOL IsFocused() const;

        /// <summary>
        /// Checks if the input was submitted (e.g., Enter key pressed).
        /// </summary>
        /// <returns>TRUE if input was submitted, FALSE otherwise.</returns>
        BOOL Submited();

        /// <summary>
        /// Sets a CGL flag for the input box.
        /// </summary>
        /// <param name="flag">The CGL flag to set.</param>
        VOID SetFlag(CGLFlags flag);

        /// <summary>
        /// Sets the title and title color for the input box.
        /// </summary>
        /// <param name="title">The title text to set.</param>
        /// <param name="col">The color of the title.</param>
        VOID SetTitle(LPCWSTR title, Color col);

    private:
        /// <summary>
        /// Renders the input box without displaying it on the screen.
        /// </summary>
        VOID RenderSilent();

        class pImpl;  // Pointer to implementation (PIMPL) idiom.
        pImpl* This = NULL;  // PIMPL instance.

        /// <summary>
        /// Returns the position of the input box.
        /// </summary>
        /// <returns>The position of the input box.</returns>
        Vector2i GetPosition() const;

        /// <summary>
        /// Returns the size of the input box.
        /// </summary>
        /// <returns>The size of the input box.</returns>
        Vector2i GetSize() const;

        /// <summary>
        /// Returns the title of the input box as a wide character string.
        /// </summary>
        /// <returns>The title of the input box.</returns>
        LPCWSTR GetTitle() const;

        /// <summary>
        /// Returns the color of the title text.
        /// </summary>
        /// <returns>The color of the title text.</returns>
        Color GetTitleColor() const;

        /// <summary>
        /// Returns the color of the border.
        /// </summary>
        /// <returns>The color of the border.</returns>
        Color GetBorderColor() const;

        /// <summary>
        /// Sets the position of the input box relative to the console window.
        /// </summary>
        /// <param name="pos">The position to set.</param>
        VOID SetPositionRelativeToConsoleWindow(Vector2i pos);

        /// <summary>
        /// Gets the character pixel at the specified value.
        /// </summary>
        /// <param name="val">The value to get the character pixel for.</param>
        /// <returns>The character pixel at the specified value.</returns>
        CharPixel GetCharPixel(INT val) const;

        friend class Panel;
    };
}