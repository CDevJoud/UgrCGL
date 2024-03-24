#pragma once
#include <RenderTarget.hpp>
namespace ugr
{
	class RenderTarget;
	class UGRCGL_API Canvas : public RenderTarget
	{
	public:
		Canvas(Vector2i size);
		VOID SetPosition(Vector2i pos);
		Vector2i GetPosition() const;
		Vector2i GetSize() const;
		CharPixel& GetPixel(int x, int y);
	private:
		friend class Sprite;
		Vector2i pos;
		RenderElements re;
	};
}