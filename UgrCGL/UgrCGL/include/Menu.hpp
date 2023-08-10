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
#include <Register.hpp>
#include <Vector.hpp>

namespace ugr
{
    class UGRCGL_API Menu
    {
    public:
        /// <summary>
        /// Destructor for the Menu class.
        /// </summary>
        ~Menu();

        /// <summary>
        /// Creates a menu with the specified size.
        /// </summary>
        /// <param name="size">The size of the menu.</param>
        VOID CreateMenu(Vector2i size);

        /// <summary>
        /// Adds elements to the menu.
        /// </summary>
        /// <param name="str">The text to add as an element.</param>
        VOID AddElements(LPCWSTR str);

        /// <summary>
        /// Sets the color of the menu.
        /// </summary>
        /// <param name="color">The color to set.</param>
        VOID SetColor(SHORT color);

        /// <summary>
        /// Sets the position where the menu becomes clickable.
        /// </summary>
        /// <param name="pos">The clickable position.</param>
        VOID SetClickablePosition(Vector2i pos);

        /// <summary>
        /// Sets the visibility of the menu.
        /// </summary>
        /// <param name="sw">TRUE to make the menu visible, FALSE to hide it.</param>
        VOID SetVisibility(BOOL sw);

    private:
        class pImpl;  // Pointer to implementation (PIMPL) idiom.
        friend class Panel;
        pImpl* m_pImpl = NULL;  // PIMPL instance.

        /// <summary>
        /// Returns the color of the menu.
        /// </summary>
        /// <returns>The color of the menu.</returns>
        Color GetColor() const;

        /// <summary>
        /// Checks if the menu is hidden.
        /// </summary>
        /// <returns>TRUE if the menu is hidden, FALSE otherwise.</returns>
        BOOL IsHidden() const;

        /// <summary>
        /// Returns the size of the menu.
        /// </summary>
        /// <returns>The size of the menu.</returns>
        Vector2i GetSize() const;

        /// <summary>
        /// Returns the clickable position of the menu.
        /// </summary>
        /// <returns>The clickable position of the menu.</returns>
        Vector2i GetClickablePosition() const;

        /// <summary>
        /// Retrieves the menu elements as a VectorMenuPair.
        /// This function returns menu text and the amount of it. **IMPORTANT** Remember to call FreeVMPGetter to free it, especially if used in a loop.
        /// </summary>
        /// <returns>The VectorMenuPair containing menu elements.</returns>
        VMP GetElements() const;

        /// <summary>
        /// Frees memory associated with a VectorMenuPair.
        /// </summary>
        /// <param name="vmp">The VectorMenuPair to free.</param>
        VOID FreeVMPGetter(VMP vmp);
    };
}