#pragma once

#ifdef UGRCGL_EXPORTS
#define UGRCGL_API __declspec(dllexport)
#else
#define UGRCGL_API __declspec(dllimport)
#endif