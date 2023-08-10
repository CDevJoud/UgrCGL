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
    class UGRCGL_API TextBox : private RenderTarget
    {
    public:
        /// <summary>
        /// Default constructor for the TextBox class.
        /// </summary>
        TextBox();

        /// <summary>
        /// Destructor for the TextBox class.
        /// </summary>
        ~TextBox();

        /// <summary>
        /// Clears the content of the text box.
        /// </summary>
        VOID Clean();

        /// <summary>
        /// Creates a text box with the specified size.
        /// </summary>
        /// <param name="size">The size of the text box.</param>
        VOID CreateBox(Vector2i size);

        /// <summary>
        /// Sets the position of the text box.
        /// </summary>
        /// <param name="pos">The position to set.</param>
        VOID SetPosition(Vector2i pos);

        /// <summary>
        /// Adds a line of text to the text box.
        /// </summary>
        /// <param name="str">The text to add.</param>
        VOID AddLine(LPCWSTR str);

        /// <summary>
        /// Sets the color of the text box.
        /// </summary>
        /// <param name="color">The color to set.</param>
        VOID SetTextBoxColor(SHORT color);

        /// <summary>
        /// Gets the current scroll position of the text box.
        /// </summary>
        /// <returns>The scroll position.</returns>
        INT GetScrollPosition() const;

        /// <summary>
        /// Moves the scroll position of the text box up.
        /// </summary>
        VOID MoveUp();

        /// <summary>
        /// Moves the scroll position of the text box down.
        /// </summary>
        VOID MoveDown();

        /// <summary>
        /// Gets the number of lines in the text box.
        /// </summary>
        /// <returns>The number of lines.</returns>
        INT GetLinesSize() const;

        /// <summary>
        /// Resets the text box to an empty state.
        /// </summary>
        VOID ResetTextBox();

    private:
        class pImpl;  // Pointer to implementation (PIMPL) idiom.
        pImpl* This;   // PIMPL instance.

        /// <summary>
        /// Renders the text box without displaying it on the screen.
        /// </summary>
        VOID RenderSilent();

        /// <summary>
        /// Returns the size of the text box.
        /// </summary>
        /// <returns>The size of the text box.</returns>
        Vector2i GetSize() const;

        /// <summary>
        /// Returns the position of the text box.
        /// </summary>
        /// <returns>The position of the text box.</returns>
        Vector2i GetPosition() const;

        /// <summary>
        /// Gets the character pixel at the specified value.
        /// </summary>
        /// <param name="val">The value to get the character pixel for.</param>
        /// <returns>The character pixel at the specified value.</returns>
        CharPixel GetCharPixel(INT val);

        /// <summary>
        /// Returns the visible height of the text box.
        /// </summary>
        /// <returns>The visible height of the text box.</returns>
        INT GetVisibileHeight() const;

        /// <summary>
        /// Returns the height of the scroll bar.
        /// </summary>
        /// <returns>The height of the scroll bar.</returns>
        INT GetScrollBarHeight() const;

        /// <summary>
        /// Returns the position of the scroll bar.
        /// </summary>
        /// <returns>The position of the scroll bar.</returns>
        Vector2i GetScrollBarPosition() const;

        /// <summary>
        /// Returns the color of the text box.
        /// </summary>
        /// <returns>The color of the text box.</returns>
        Color GetColor() const;

        friend class Panel;
    };
}