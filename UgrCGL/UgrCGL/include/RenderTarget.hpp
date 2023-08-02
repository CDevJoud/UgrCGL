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
		/// <summary>
		/// Renders a single pixel in the buffer.
		/// </summary>
		/// <param name="pos">The position of the pixel.</param>
		/// <param name="c">The character to be displayed at the specified position.</param>
		/// <param name="color">The color of the pixel.</param>
		/// <remarks>
		/// This function is used to render a single pixel on the screen buffer at the specified position,
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
		/// <summary>
		/// This function finds the clipped position of a 2D point.
		/// If any given point has a negative value or a value larger than the screen size,
		/// it will automatically limit the point to keep it within the screen boundaries.
		/// </summary>
		/// <param name="x">The point x to be clipped. The function will modify this
		/// parameter if it is outside the screen bounds.</param>
		/// <param name="y">The point y to be clipped. The function will modify this
		/// parameter if it is outside the screen bounds.</param>
		VOID CalculateClipOn(SHORT x, SHORT y);
		/// <summary>
		/// Fills a section defined by two 2D points with the specified character and color.
		/// </summary>
		/// <param name="p1">The first 2D point defining one corner of the section.</param>
		/// <param name="p2">The second 2D point defining the opposite corner of the section.</param>
		/// <param name="c">The character to be used for filling the section. (Default: 0x2588)</param>
		/// <param name="color">The color to be applied to the filled section. (Default: 0x0F)</param>
		VOID Fill(Vector2i p1, Vector2i p2, SHORT c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Fills a section defined by two 2D points with the specified character and color.
		/// </summary>
		/// <param name="rect">The ShortRect holds both the corner of the section and the oppoisite corner.</param>
		/// <param name="c">The character to be used for filling the section. (Default: 0x2588)</param>
		/// <param name="color">The color to be applied to the filled section. (Default: 0x0F)</param>
		VOID Fill(ShortRect rect, SHORT c = 0x2588, Color color = 0x0F);
		
		/// <summary>
		/// Renders a line in the buffer using two 2D points.
		/// </summary>
		/// <param name="p1">The starting point of the line.</param>
		/// <param name="p2">The ending point of the line.</param>
		/// <param name="c">The character to be used for rendering the line. (Default: 0x2588)</param>
		/// <param name="color">The color of the line. (Default: 0x0F)</param>
		VOID RenderLine(Vector2i p1, Vector2i p2, SHORT c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Renders a line in the buffer using two 2D points.
		/// </summary>
		/// <param name="rect"> The ShortRect holds both the first point and second point.</param>
		/// <param name="c">The character to be used for rendering the line. (Default: 0x2588)</param>
		/// <param name="color">The color of the line. (Default: 0x0F)</param>}
		VOID RenderLine(ShortRect rect, SHORT c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Renders a triangle in the buffer using 3 points
		/// </summary>
		VOID RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, SHORT c = 0x2588, Color color = 0x0F);
		VOID RenderTriangle(VAO p, SHORT c, Color color = 0x0F);
	private:
		RenderElements re;
	};
}