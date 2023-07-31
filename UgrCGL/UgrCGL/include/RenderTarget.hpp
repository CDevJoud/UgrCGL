#pragma once
#include <Windows.h>
#include <Register.hpp>
namespace ugr
{
	struct UGRCGL_API RenderElements
	{
		HANDLE hConsole = NULL;
		CHAR_INFO* buffer = NULL;
		COORD screen{};
		SMALL_RECT rect{};
	};
	class UGRCGL_API RenderTarget
	{
	public:
		/// <summary>
		/// Initializes the RenderTarget by providing the necessary RenderElements.
		/// </summary>
		/// <param name="re">The RenderElements used to set up the RenderTarget.</param>
		///
		/// <remarks>
		/// The RenderTarget is responsible for managing the rendering process, utilizing the provided RenderElements
		/// to define how the graphics and elements should be displayed on the screen.
		/// </remarks>
		VOID InitRenderTarget(RenderElements re);
		/// <summary>
		/// Draws a single pixel in the buffer.
		/// </summary>
		/// <param name="pos">The position of the pixel.</param>
		/// <param name="c">The character to be displayed at the specified position.</param>
		/// <param name="color">The color of the pixel.</param>
		/// <remarks>
		/// This function is used to draw a single pixel on the screen buffer at the specified position,
		/// using the provided character and color.
		/// </remarks>
		VOID SetPixel(COORD pos, SHORT c = 0x2588, BYTE color = 0x0F);
	private:
		RenderElements re;
	};
}