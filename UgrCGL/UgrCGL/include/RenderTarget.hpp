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
		VOID SetPixel(Vector2i pos, CharSurface c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Clears the screen buffer, preparing it for rendering the next frame.
		/// </summary>
		/// <remarks>
		/// Call this function at the beginning of every frame to clear the screen and avoid viewing artifacts from the previous frame.
		/// </remarks>
		/// <param name="c">The character used to fill the screen. (Default: 0x2588)</param>
		/// <param name="color">The color applied to the screen. (Default: 0x00)</param>
		VOID ClearScreen(CharSurface c = 0x2588, Color color = 0x00);
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
		VOID Fill(Vector2i p1, Vector2i p2, CharSurface c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Fills a section defined by two 2D points with the specified character and color.
		/// </summary>
		/// <param name="rect">The ShortRect holds both the corner of the section and the oppoisite corner.</param>
		/// <param name="c">The character to be used for filling the section. (Default: 0x2588)</param>
		/// <param name="color">The color to be applied to the filled section. (Default: 0x0F)</param>
		VOID Fill(ShortRect rect, CharSurface c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Renders a line in the buffer using two 2D points.
		/// </summary>
		/// <param name="p1">The starting point of the line.</param>
		/// <param name="p2">The ending point of the line.</param>
		/// <param name="c">The character to be used for rendering the line. (Default: 0x2588)</param>
		/// <param name="color">The color of the line. (Default: 0x0F)</param>
		VOID RenderLine(Vector2i p1, Vector2i p2, CharSurface c = 0x2588, Color color = 0x0F);
		/// <summary>
		/// Renders a line in the buffer using two 2D points.
		/// </summary>
		/// <remarks>
		/// This function utilizes the Bresenham line algorithm to render a line segment
		/// on the screen, connecting the two specified points. For more details on the algorithm,
		/// refer to: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
		/// </remarks>
		/// <param name="rect">A ShortRect holding the coordinates of the first and second points.</param>
		/// <param name="c">The character to be used for rendering the line. (Default: 0x2588, a solid block)</param>
		/// <param name="color">The color of the line. (Default: 0x0F, white on black)</param>
		VOID RenderLine(ShortRect rect, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Renders a triangle using three specified points.
		/// </summary>
		/// <param name="p1">First vertex of the triangle.</param>
		/// <param name="p2">Second vertex of the triangle.</param>
		/// <param name="p3">Third vertex of the triangle.</param>
		/// <param name="c">Character representing the fill of the triangle (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RenderTriangle(Vector2i p1, Vector2i p2, Vector2i p3, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Renders a triangle using a VertexArrayObject (VAO).
		/// </summary>
		/// <param name="p">Pointer to the VertexArrayObject (VAO) containing vertex data.</param>
		/// <param name="c">Character representing the fill of the triangle (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RenderTriangle(VAO* p, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Renders a quad using two sets of points defined by ShortRect structures.
		/// </summary>
		/// <param name="rect1">First ShortRect defining two points of the quad.</param>
		/// <param name="rect2">Second ShortRect defining two additional points of the quad.</param>
		/// <param name="c">Character representing the fill of the quad (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RenderQuad(ShortRect rect1, ShortRect rect2, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Renders a quad at the specified position with a given size.
		/// </summary>
		/// <param name="rect">The ShortRect specifying the position and size of the quad.</param>
		/// <param name="c">Character representing the fill of the quad (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RenderQuad(ShortRect rect, CharSurface c = 0x2588, Color color = 0x0F);

		VOID RenderQuad(Vector2i p1, Vector2i p2, Vector2i p3, Vector2i p4, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Renders ASCII text at the specified position.
		/// </summary>
		/// <param name="pos">The position where the top-left corner of the text will be rendered.</param>
		/// <param name="str">The null-terminated ASCII string to be rendered.</param>
		/// <param name="color">Color of the text (default: 0x0F, white on black).</param>
		/// <param name="_Flags_">Additional rendering flags to control text display (default: NULL).</param>
		VOID RenderText(Vector2i pos, LPCSTR str, Color color = 0x0F, CGLFlags _Flags_ = NULL);

		/// <summary>
		/// Renders wide (Unicode) text at the specified position.
		/// </summary>
		/// <param name="pos">The position where the top-left corner of the text will be rendered.</param>
		/// <param name="str">The null-terminated wide text string (LPCWSTR) to be rendered.</param>
		/// <param name="color">Color of the text (default: 0x0F, white on black).</param>
		/// <param name="_Flags_">Additional rendering flags to control text display (default: NULL).</param>
		VOID RenderText(Vector2i pos, LPCWSTR str, Color color = 0x0F, CGLFlags _Flags_ = NULL);

		/// <summary>
		/// Renders a circle on the screen using Bresenham's circle algorithm.
		/// </summary>
		/// <param name="p1">The center of the circle.</param>
		/// <param name="radius">The radius of the circle.</param>
		/// <param name="c">Character representing the fill of the circle (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		/// <param name="VertexShader">Custom vertex shader function (default: NULL).</param>
		/// <remarks>The default shader provides a basic circle drawing algorithm.</remarks>
		/// \code 
		/// void VertexShader(int& p, int& x, int& y)
		/// {
		/// 	p += (p <= 0) ? 4 * x++ + 6 : 4 * (x++ - y--) + 10;
		/// }
		/// \endcode
		/// **Check This Out!**
		/// \code
		/// int xx = 1;
		/// int yy = 1;
		/// void VertexShader(int& p, int& x, int& y)
		/// {
		/// 	x += xx;
		/// 	y -= yy;
		/// 	p += (p <= 0) ? 4 * (x += 6) : 4 * (x += 10 - y) + 10;
		/// }
		/// 
		/// class Demo : public ugr::ConsoleWindow
		/// {
		/// public:
		/// 	Demo()
		/// 	{
		/// 		this->InitConsoleWindow();
		/// 		this->CreateConsoleBufferWindow(ugr::Vector2i(240, 128), ugr::Vector2i(8, 8));
		/// 	}
		/// 	int run()
		/// 	{
		/// 		this->ClearScreen(0x2588, 0x06);
		/// 		while (true)
		/// 		{
		/// 			xx++;
		/// 			yy += 0.05;
		/// 			this->RenderCircle(ugr::Vector2i(120, 64), 60, 0x2588, 0x01, VertexShader);
		/// 			this->Display();
		/// 		}
		/// 		this->ShutDown();
		/// 		return 0;
		/// 	}
		/// };
		/// 
		/// int main()
		/// {
		/// 	Demo d;
		/// 	return d.run();
		/// }
		/// 
		/// /// \endcode
		VOID RenderCircle(Vector2i p1, INT radius, CharSurface c = 0x2588, Color color = 0x0F, VOID(*VertexShader)(int& p, int& x, int& y) = NULL);

		/// <summary>
		/// Rasterizes a filled triangle using three specified 2D points.
		/// </summary>
		/// <param name="p1">First vertex of the triangle.</param>
		/// <param name="p2">Second vertex of the triangle.</param>
		/// <param name="p3">Third vertex of the triangle.</param>
		/// <param name="c">Character representing the fill of the triangle (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RasterizeTriangle(Vector2i p1, Vector2i p2, Vector2i p3, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Rasterizes a filled circle using the specified center and radius.
		/// </summary>
		/// <param name="p1">The center of the circle.</param>
		/// <param name="r">The radius of the circle.</param>
		/// <param name="c">Character representing the fill of the circle (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		/// <param name="VertexShader">Custom vertex shader function (default: NULL).</param>
		/// <remarks>The default shader provides a basic circle drawing algorithm.</remarks>
		/// \code 
		/// void VertexShader(int& p, int& x, int& y)
		/// {
		/// 	p += (p <= 0) ? 4 * x++ + 6 : 4 * (x++ - y--) + 10;
		/// }
		/// \endcode
		VOID RasterizeCircle(Vector2i p1, INT r, CharSurface c = 0x2588, Color color = 0x0F, VOID(*VertexShader)(int& p, int& x, int& y) = NULL);

		/// <summary>
		/// Rasterizes a filled quad using the specified position and width.
		/// </summary>
		/// <param name="rect">The ShortRect specifying the position and width of the quad.</param>
		/// <param name="c">Character representing the fill of the quad (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RasterizeQuad(ShortRect rect, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Rasterizes a filled quad using four specified points.
		/// </summary>
		/// <param name="rect1">The first ShortRect defining two points of the quad.</param>
		/// <param name="rect2">The second ShortRect defining the other two points of the quad.</param>
		/// <param name="c">Character representing the fill of the quad (default: 0x2588, a solid block).</param>
		/// <param name="color">Color of the fill (default: 0x0F, white on black).</param>
		VOID RasterizeQuad(ShortRect rect1, ShortRect rect2, CharSurface c = 0x2588, Color color = 0x0F);

		/// <summary>
		/// Checks if a position is within the boundaries of a rectangle.
		/// </summary>
		/// <param name="pos">The position to check.</param>
		/// <param name="rect">The ShortRect defining the rectangle's position and size.</param>
		/// <returns>TRUE if the position is within the rectangle's boundaries, otherwise FALSE.</returns>
		BOOL CheckInBoundaries(Vector2i pos, ShortRect rect);

	private:
		/**
		 * Corrects the conversion of ASCII code to Unicode.
		 *
		 * This function corrects the conversion of a given ASCII code to its corresponding Unicode value.
		 *
		 * @param c The ASCII code to be corrected.
		 * @return The corrected Unicode value.
		 */
		SHORT CorrectConversion(BYTE c);
		RenderElements re;
	};
}