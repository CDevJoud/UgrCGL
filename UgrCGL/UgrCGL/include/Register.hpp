#pragma once
#define VOID void
#define NULL 0
#ifdef UGRCGL_EXPORTS
#define UGRCGL_API __declspec(dllexport)
#else
#define UGRCGL_API __declspec(dllimport)
#endif

namespace ugr
{
	typedef void* HANDLE;
	typedef short SHORT;
	typedef short CharSurface;
	typedef unsigned char Color;
	typedef char CHAR;
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
}
