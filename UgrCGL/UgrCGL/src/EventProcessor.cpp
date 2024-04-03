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

     EventProcessor::KeyStrokesCondition EventProcessor::m_KeyboardCondition[256]{};
     EventProcessor::KeyStrokesCondition EventProcessor::m_MouseCondition[5]{};
     SHORT                               EventProcessor::m_NewKeyboardCondition[256]{};
     SHORT                               EventProcessor::m_OldKeyboardCondition[256]{};
     bool                                EventProcessor::m_OldMouseCondition[5]{};
     bool                                EventProcessor::m_NewMouseCondition[5]{};

     Vector2i  EventProcessor::m_mousePos;
     HANDLE  EventProcessor::m_handleConsoleInput;
     InputRecord  EventProcessor::mapKeys;
     BOOL  EventProcessor::ShiftOn;

    EventProcessor::EventProcessor(HANDLE CIN)
    {
        this->m_handleConsoleInput = CIN;
    }
    VOID EventProcessor::ProcessEvents()
    {
        //Handle KeyBoard Input
        for (INT i = 0; i < 256; i++)
        {
            m_NewKeyboardCondition[i] = GetAsyncKeyState(i);

            m_KeyboardCondition[i].bStrokePressed = FALSE;
            m_KeyboardCondition[i].bStrokeReleased = FALSE;

            if (m_NewKeyboardCondition[i] != m_OldKeyboardCondition[i])
            {
                if (m_NewKeyboardCondition[i] & 0x8000)
                {
                    m_KeyboardCondition[i].bStrokePressed = !m_KeyboardCondition[i].bStrokeIsHeld;
                    m_KeyboardCondition[i].bStrokeIsHeld = TRUE;
                }
                else
                {
                    m_KeyboardCondition[i].bStrokeReleased = TRUE;
                    m_KeyboardCondition[i].bStrokeIsHeld = FALSE;
                }
            }
            m_OldKeyboardCondition[i] = m_NewKeyboardCondition[i];
        }

        SetConsoleMode(m_handleConsoleInput, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);

        //Handle Mouse Input
        INPUT_RECORD inBuf[32];
        DWORD events = 0;
        GetNumberOfConsoleInputEvents(m_handleConsoleInput, &events);
        if (events > 0)
            ReadConsoleInput(m_handleConsoleInput, (PINPUT_RECORD)&inBuf, events, &events);

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
                    m_mousePos.x = inBuf[i].Event.MouseEvent.dwMousePosition.X;
                    m_mousePos.y = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
                }
                break;

                case 0:
                {
                    for (int m = 0; m < 5; m++)
                        m_NewMouseCondition[m] = (inBuf[i].Event.MouseEvent.dwButtonState & (1 << m)) > 0;
                }
                break;

                default:
                    break;
                }
            }
            break;

            default:
                break;
                
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
    EventProcessor::KeyStrokesCondition EventProcessor::Keyboard(INT ID)
    {
        return m_KeyboardCondition[ID];
    }
    Vector2i EventProcessor::GetMousePos()
    {
        return m_mousePos;
    }
    EventProcessor::KeyStrokesCondition EventProcessor::Mouse(MouseType ID)
    {
        switch (ID)
        {
        case MouseType::Left:
            return m_MouseCondition[0];
        case MouseType::Right:
            return m_MouseCondition[1];
        case MouseType::Middle:
            return m_MouseCondition[2];
        default:
            break;
        }
    }
    WCHAR EventProcessor::GetText()
    {
        if (Keyboard(L'Q').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Q'; else return L'q';
        if (Keyboard(L'W').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'W'; else return L'w';
        if (Keyboard(L'E').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'E'; else return L'e';
        if (Keyboard(L'R').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'R'; else return L'r';
        if (Keyboard(L'T').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'T'; else return L't';
        if (Keyboard(L'Y').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Y'; else return L'y';
        if (Keyboard(L'U').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'U'; else return L'u';
        if (Keyboard(L'I').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'I'; else return L'i';
        if (Keyboard(L'O').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'O'; else return L'o';
        if (Keyboard(L'P').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'P'; else return L'p';
        if (Keyboard(L'A').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'A'; else return L'a';
        if (Keyboard(L'S').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'S'; else return L's';
        if (Keyboard(L'D').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'D'; else return L'd';
        if (Keyboard(L'F').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'F'; else return L'f';
        if (Keyboard(L'G').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'G'; else return L'g';
        if (Keyboard(L'H').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'H'; else return L'h';
        if (Keyboard(L'J').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'J'; else return L'j';
        if (Keyboard(L'K').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'K'; else return L'k';
        if (Keyboard(L'L').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'L'; else return L'l';
        if (Keyboard(L'Z').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Z'; else return L'z';
        if (Keyboard(L'X').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'X'; else return L'x';
        if (Keyboard(L'C').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'C'; else return L'c';
        if (Keyboard(L'V').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'V'; else return L'v';
        if (Keyboard(L'B').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'B'; else return L'b';
        if (Keyboard(L'N').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'N'; else return L'n';
        if (Keyboard(L'M').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'M'; else return L'm';

        // ÅÄÖ Will be fixed later!
        if (Keyboard( 221).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Å'; else return L'å';
        if (Keyboard( 222).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Ä'; else return L'ä';
        if (Keyboard( 192).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'Ö'; else return L'ö';

        if (Keyboard(L'0').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'='; else return L'0';
        if (Keyboard(L'1').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'!'; else return L'1';
        if (Keyboard(L'2').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'"'; else return L'2';
        if (Keyboard(L'3').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'#'; else return L'3';
        if (Keyboard(L'4').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'¤'; else return L'4';
        if (Keyboard(L'5').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'%'; else return L'5';
        if (Keyboard(L'6').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'&'; else return L'6';
        if (Keyboard(L'7').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'/'; else return L'7';
        if (Keyboard(L'8').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'('; else return L'8';
        if (Keyboard(L'9').bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L')'; else return L'9';
        if (Keyboard( 187).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'?'; else return L'+';
        
        
        if (Keyboard( 226).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L'>'; else return L'<';
        if (Keyboard( 190).bStrokePressed) if (Keyboard(VK_SHIFT).bStrokeIsHeld) return L':'; else return L'.';

        if (Keyboard(VK_ESCAPE).bStrokePressed) return VK_ESCAPE;
        if (Keyboard(VK_RETURN).bStrokePressed) return VK_RETURN;
        if (Keyboard(VK_SPACE).bStrokePressed) return VK_SPACE;
        if (Keyboard(VK_BACK).bStrokePressed) return VK_BACK;

        return NULL;
    }
}