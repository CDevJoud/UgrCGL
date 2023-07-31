#pragma once
namespace ugr
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2<T>()
		{
			this->x = 0;
			this->y = 0;
		}
		Vector2<T>(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		Vector2<T> operator+(Vector2<T>& i)
		{
			Vector2<T> o;
			o.x = x + i.x;
			o.y = y + i.y;
			return o;
		}
		Vector2<T> operator-(Vector2<T>& i)
		{
			Vector2<T> o;
			o.x = x - i.x;
			o.y = y - i.y;
			return o;
		}
		T x, y;
	};

	typedef Vector2<int> Vector2i;
}