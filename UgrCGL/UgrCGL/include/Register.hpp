/*****************************************************************//**
* \file   RenderTarget.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   02/Aug/2023
*********************************************************************/
/*****************************************************************//**
* \file   ConsoleWindow.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   02/Aug/2023
*********************************************************************/
/*****************************************************************//**
* \file   Vector.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   02/Aug/2023
*********************************************************************/
/*****************************************************************//**
 * \file   UgrCGL.hpp
 * \copyright (C) MIT License 2022-2023 Joud Kandeel
 *
 * \author CDevJoud
 * \date   02/Aug/2023
 *********************************************************************/
/*****************************************************************//**
* \file   Panel.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   02/Aug/2023
*********************************************************************/
/*****************************************************************//**
* \file   EventProcessor.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   02/Aug/2023
*********************************************************************/
/*****************************************************************//**
* \file   InputBox.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   10/Aug/2023
*********************************************************************/
/*****************************************************************//**
* \file   TextBox.hpp
* \copyright (C) MIT License 2022-2023 Joud Kandeel
*
* \author CDevJoud
* \date   10/Aug/2023
*********************************************************************/
#pragma once
#define VOID void
#define NULL 0

//RenderTarget Flags

/// This flag enable new line detection for the \link RenderText() \endlink function allows it to detect if there was a new line character.
/// when it finds one it will jump into a new line.
/// **Usage Example:**
/// \code{.cpp}
/// this->RenderText(ugr::Vector2i(10, 10), "Hello World\nThis is a new line!", 0x0F, RT_ENABLE_NEWLINE_DETECTION);
/// \endcode
/// 
/// \see RenderText()
/// 
#define RT_ENABLE_NEWLINE_DETECTION 0x01

///
/// This flag enables correction for Unicode characters when input as a string. The \ref RenderText() function can detect if a Unicode character is present and correct its byte representation.
///
/// For example, when attempting to render the character "ä", the input bytes might be 0xEF 0xFF. With this flag enabled, it will be corrected to 0xEF 0x00.
///
/// **Usage Example:**
/// \code{.cpp}
/// this->RenderText(ugr::Vector2i(10, 10), "Hallå där!", 0x0F, RT_ENABLE_CORRECT_CONVERT);
/// \endcode
///
/// \see \ref RenderText()
///
/// \def RT_ENABLE_CORRECT_CONVERT
/// This macro defines the flag value (0x02) that enables Unicode character correction during text rendering.
///
#define RT_ENABLE_CORRECT_CONVERT   0x02

#define RT_RENDER_SMOOTHRECT 0x01

#define ENABLE_INPUT_ON_RETURN 0x01
//RenderTarget Flags

#ifdef UGRCGL_EXPORTS
#define UGRCGL_API __declspec(dllexport)
#else
#define UGRCGL_API __declspec(dllimport)
#endif
#define TRUE 1
#define FALSE 0

namespace ugr
{
	typedef int BOOL;
	typedef unsigned long long CGLFlags;
	typedef unsigned long DWORD;
	typedef unsigned int UINT;
	typedef int INT;
	typedef float FLOAT;
	typedef float VAO;
	typedef const char* LPCSTR;
	typedef const wchar_t* LPCWSTR;
	typedef  wchar_t* LPWSTR;
	typedef const char* PCSTR;
	typedef const wchar_t* PCWSTR;
	typedef void* HANDLE;
	typedef short SHORT;
	typedef short *PSHORT;
	typedef unsigned short WORD;
	typedef short CharSurface;
	typedef unsigned char Color;
	typedef unsigned char BYTE;
	typedef char CHAR;
	typedef struct _COORD {
		SHORT X;
		SHORT Y;
	} COORD, * PCOORD;
	typedef struct _s_CharPixel {
		union {
			wchar_t UnicodeChar;
			char   AsciiChar;
		} Char;
		unsigned short Color;
	} CharPixel, * PCharPixel, *ScreenBuffer;
	typedef struct _s_ShortRect {
		SHORT x;
		SHORT y;
		SHORT width;
		SHORT height;
	} ShortRect, *PShortRect;
	typedef struct _WINDOW_BUFFER_SIZE_RECORD {
		COORD dwSize;
	} WINDOW_BUFFER_SIZE_RECORD, * PWINDOW_BUFFER_SIZE_RECORD;

	typedef struct _MENU_EVENT_RECORD {
		UINT dwCommandId;
	} MENU_EVENT_RECORD, * PMENU_EVENT_RECORD;

	typedef struct _FOCUS_EVENT_RECORD {
		BOOL bSetFocus;
	} FOCUS_EVENT_RECORD, * PFOCUS_EVENT_RECORD;

	typedef struct _KEY_EVENT_RECORD {
		BOOL bKeyDown;
		WORD wRepeatCount;
		WORD wVirtualKeyCode;
		WORD wVirtualScanCode;
		union {
			wchar_t UnicodeChar;
			char   AsciiChar;
		} uChar;
		DWORD dwControlKeyState;
	} KEY_EVENT_RECORD, * PKEY_EVENT_RECORD;

	typedef struct _MOUSE_EVENT_RECORD {
		COORD dwMousePosition;
		DWORD dwButtonState;
		DWORD dwControlKeyState;
		DWORD dwEventFlags;
	} MOUSE_EVENT_RECORD, * PMOUSE_EVENT_RECORD;

	typedef struct _INPUT_RECORD {
		WORD EventType;
		union {
			KEY_EVENT_RECORD KeyEvent;
			MOUSE_EVENT_RECORD MouseEvent;
			WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
			MENU_EVENT_RECORD MenuEvent;
			FOCUS_EVENT_RECORD FocusEvent;
		} Event;
	} InputRecord, *pInputRecord;
	typedef struct _VecMenuPair
	{
		DWORD size;
		LPWSTR* dStrW;
	}VMP;
}