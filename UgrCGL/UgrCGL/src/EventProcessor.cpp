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
#include <Windows.h>
#include <EventProcessor.hpp>
#include <conio.h>

namespace ugr
{
    EventProcessor::EventProcessor(HANDLE CIN)
    {
        this->m_handleConsoleInput = CIN;
    }

    VOID EventProcessor::ProcessEvents()
    {
        //Handle KeyBoard Input
        for (INT i = 0; i < 256; i++)
        {
            this->m_NewKeyboardCondition[i] = GetAsyncKeyState(i);

            this->m_KeyboardCondition[i].bStrokePressed = FALSE;
            this->m_KeyboardCondition[i].bStrokeReleased = FALSE;

            if (this->m_NewKeyboardCondition[i] != this->m_OldKeyboardCondition[i])
            {
                if (this->m_NewKeyboardCondition[i] & 0x8000)
                {
                    this->m_KeyboardCondition[i].bStrokePressed = !this->m_KeyboardCondition[i].bStrokeIsHeld;
                    this->m_KeyboardCondition[i].bStrokeIsHeld = TRUE;
                }
                else
                {
                    this->m_KeyboardCondition[i].bStrokeReleased = TRUE;
                    this->m_KeyboardCondition[i].bStrokeIsHeld = FALSE;
                }
            }
            this->m_OldKeyboardCondition[i] = this->m_NewKeyboardCondition[i];
        }

        SetConsoleMode(this->m_handleConsoleInput, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);

        //Handle Mouse Input
        INPUT_RECORD inBuf[32];
        DWORD events = 0;
        GetNumberOfConsoleInputEvents(this->m_handleConsoleInput, &events);
        if (events > 0)
            ReadConsoleInput(this->m_handleConsoleInput, (PINPUT_RECORD)&inBuf, events, &events);

        for (DWORD i = 0; i < events; i++)
        {
            switch (inBuf[i].EventType)
            {
            case MOUSE_EVENT:
            {
                switch (inBuf[i].Event.MouseEvent.dwEventFlags)
                {
                case MOUSE_MOVED:
                {
                    this->m_mousePos.x = inBuf[i].Event.MouseEvent.dwMousePosition.X;
                    this->m_mousePos.y = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
                }
                break;

                case 0:
                {
                    for (int m = 0; m < 5; m++)
                        this->m_NewMouseCondition[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
                }
                break;

                default:
                    break;
                }
            }
            break;

            default:
                break;
                // We don't care just at the moment
            }
        }
        for (int m = 0; m < 5; m++)
        {
            m_MouseCondition[m].bStrokePressed = false;
            m_MouseCondition[m].bStrokeReleased = false;

            if (m_NewMouseCondition[m] != m_OldMouseCondition[m])
            {
                if (m_NewMouseCondition[m])
                {
                    m_MouseCondition[m].bStrokePressed = true;
                    m_MouseCondition[m].bStrokeIsHeld = true;
                }
                else
                {
                    m_MouseCondition[m].bStrokeReleased = true;
                    m_MouseCondition[m].bStrokeIsHeld = false;
                }
            }

            m_OldMouseCondition[m] = m_NewMouseCondition[m];
        }
    }
    VOID EventProcessor::InitEventProcessor(HANDLE hConsoleInput)
    {
        this->m_handleConsoleInput = hConsoleInput;
    }
    EventProcessor::KeyStrokesCondition EventProcessor::Mouse(MouseType ID)
    {
        switch (ID)
        {
        case MouseType::Left:
            return this->m_MouseCondition[0];
        case MouseType::Right:
            return this->m_MouseCondition[1];
        case MouseType::Middle:
            return this->m_MouseCondition[2];
        default:
            break;
        }
    }
}