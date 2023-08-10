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
#include <RenderTarget.hpp>
#include <EventProcessor.hpp>

namespace ugr
{
	class UGRCGL_API InputBox : private RenderTarget
	{
	public:
		InputBox();
		~InputBox();
		VOID CreateBox(Vector2i size);
		VOID SetPosition(Vector2i pos);
		VOID Clean();
		VOID ProcessEvents(EventProcessor* EP);
		LPCWSTR GetStrInputW() const;
		LPCSTR GetStrInput() const;
		VOID SetStrInput(LPCWSTR str);
		VOID ResetStrInput();
		BOOL IsFocused() const;
		BOOL Submited();
		VOID SetFlag(CGLFlags flag);
		VOID SetTitle(LPCWSTR title, Color col);
	private:
		VOID RenderSilent();
		class pImpl;
		pImpl* This = NULL;
		Vector2i GetPosition() const;
		Vector2i GetSize() const;
		LPCWSTR GetTitle() const;
		Color GetTitleColor() const;
		Color GetBorderColor() const;
		VOID SetPositionRelativeToConsoleWindow(Vector2i pos);
		CharPixel GetCharPixel(INT val) const;
		friend class Panel;
	};
}