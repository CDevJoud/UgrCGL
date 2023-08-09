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
	class UGRCGL_API Menu
	{
	public:
		~Menu();
		VOID CreateMenu(Vector2i size);
		VOID AddElements(LPCWSTR str);
		VOID SetColor(SHORT color);
		VOID SetClickablePosition(Vector2i pos);
		VOID SetVisibility(BOOL sw);
	private:
		class pImpl;
		friend class Panel;
		pImpl* m_pImpl = NULL;

		Color GetColor() const;
		BOOL IsHidden() const;
		Vector2i GetSize() const;
		Vector2i GetClickablePosition() const;

		/// <summary>
		/// VectorMenuPair.
		/// This Function Will return menu text and amount of it. **IMPORTANT** remember to call FreeVMPGetter to free it!"If You use it in a loop"
		/// </summary>
		/// <returns>VMP</returns>
		VMP GetElements() const;
		VOID FreeVMPGetter(VMP vmp);
	};
}