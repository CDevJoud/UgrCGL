#pragma once
#include <Canvas.hpp>

namespace ugr
{
	class Canvas;
	class UGRCGL_API Sprite
	{
	public:
		typedef struct S_SprHeader
		{
			int version; //In hex
			int x, y;
		}*PSprHeader, SprHeader;
		Sprite();
		Sprite(LPCWSTR fileName);
		BOOL LoadSpriteFromFile(LPCWSTR fileName);
		BOOL LoadSpriteFromFile(LPCSTR fileName);
		VOID LoadSpriteFromCanvas(Canvas* c);
		VOID SaveSpriteToFile(LPCWSTR fileName);
		CharPixel GetPixel(int x, int y) const;
		Vector2i GetSize() const;
	private:
		
		friend class Canvas;
		class pImpl;
		pImpl* This = nullptr;
	};
}