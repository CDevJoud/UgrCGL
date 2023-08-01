#pragma once
#include <Register.hpp>
#include <Vector.hpp>
namespace ugr
{
	struct UGRCGL_API RenderElements
	{
		HANDLE hConsole = NULL;
		ScreenBuffer buffer = NULL;
		Vector2i screen{};
		ShortRect rect{};
	};
	class UGRCGL_API RenderTarget
	{
	public:
		/// <summary>
		/// Initializes the RenderTarget by providing the necessary RenderElements.
		/// </summary>
		/// <param name="re">The RenderElements used to set up the RenderTarget.</param>
		/// The RenderTarget is responsible for managing the rendering process, utilizing the provided RenderElements
		/// to define how the graphics and elements should be displayed on the screen.
		/// </remarks>
		/// \warning This function should be called in the constructor or in an init function otherwise it won't be able to render graphics in the buffer
		VOID InitRenderTarget(RenderElements re);
		// <summary>
		/// Draws a single pixel in the buffer.
		/// </summary>
		/// <param name="pos">The position of the pixel.</param>
		/// <param name="c">The character to be displayed at the specified position.</param>
		/// <param name="color">The color of the pixel.</param>
		/// <remarks>
		/// This function is used to draw a single pixel on the screen buffer at the specified position,
		/// using the provided character and color.
		/// </remarks>
		/// \note if you specify a negative coordinate the SetPixel() function will not render it!
		VOID SetPixel(Vector2i pos, SHORT c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// This function finds the clipped position of a 2D point.
		/// If any given point has a negative value or a value larger than the screen size,
		/// it will automatically limit the point to keep it within the screen boundaries.
		/// </summary>
		/// <param name="i">The 2D point to be clipped. The function will modify this
		/// parameter if it is outside the screen bounds.</param>
		VOID CalculateClipOn(Vector2i& i);
	private:
		RenderElements re;
	};
}