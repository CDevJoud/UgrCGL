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
#include <Vector.hpp>
#include <Register.hpp>
namespace ugr
{
    class UGRCGL_API EventProcessor
    {
    public:
        struct KeyStrokesCondition
        {
            bool bStrokePressed;
            bool bStrokeReleased;
            bool bStrokeIsHeld;
        };
        static KeyStrokesCondition m_KeyboardCondition[256];
        static KeyStrokesCondition m_MouseCondition[5];
        static SHORT               m_NewKeyboardCondition[256];
        static SHORT               m_OldKeyboardCondition[256];
        static bool                m_OldMouseCondition[5];
        static bool                m_NewMouseCondition[5];

        static Vector2i m_mousePos;  // Mouse position relative to the console window.
        static HANDLE m_handleConsoleInput; // Handle to the console input.
        static InputRecord mapKeys;  // Input record for mapping keys.
        static BOOL ShiftOn; // Flag indicating if the Shift key is pressed.

    public:
        /// <summary>
        /// Default constructor for the EventProcessor class.
        /// </summary>
        EventProcessor() = default;

        /// <summary>
        /// Constructor for the EventProcessor class.
        /// </summary>
        /// <param name="consoleInput">Handle to the console input.</param>
        EventProcessor(HANDLE consoleInput);

        enum class MouseType
        {
            Left = 0, Right, Middle
        };

        /// <summary>
        /// Monitors keyboard events associated with the specified ID, such as clicks or interactions.
        /// </summary>
        /// <param name="ID">The unique identifier for the keyboard event being monitored.</param>
        /// <returns>Returns a KeyStrokesCondition indicating the current state of the keyboard event.</returns>
        static KeyStrokesCondition Keyboard(INT ID);

        /// <summary>
        /// Retrieves the mouse position relative to the console window.
        /// </summary>
        /// <returns>A Vector2i representing the mouse coordinates.</returns>
        static Vector2i GetMousePos();

        /// <summary>
        /// Checks for mouse click events.
        /// </summary>
        /// <param name="ID">The type of mouse button to check.</param>
        /// <returns>Returns a KeyStrokesCondition indicating the state of the mouse event.</returns>
        static KeyStrokesCondition Mouse(MouseType ID);

        /// <summary>
        /// Processes console input events.
        /// </summary>
        static VOID ProcessEvents();

        static wchar_t GetText();
    protected:
        /// <summary>
        /// Initializes the EventProcessor with the provided console input handle.
        /// </summary>
        /// <param name="hConsoleInput">Handle to the console input.</param>
        VOID InitEventProcessor(HANDLE hConsoleInput);
    };
}