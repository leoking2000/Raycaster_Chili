#pragma once
#include "Vector2.h"

namespace Shape
{
	template<typename T>
	class _Rectangle
	{
	public:
		_Rectangle() = default;
		_Rectangle(T left_in, T right_in, T top_in, T bottom_in)
			:
			left(left_in),
			right(right_in),
			top(top_in),
			bottom(bottom_in)
		{
		}
		_Rectangle(const Vector2& topLeft, const Vector2& bottomRight)
			:
			_Rectangle( (T)topLeft.x , (T)bottomRight.x , (T)topLeft.y , (T)bottomRight.y )
		{
		}
		_Rectangle(const Vector2& topLeft, T width, T height)
			:
			_Rectangle(topLeft, topLeft + Vector2( (float)width , (float)height ))
		{
		}


		bool IsOverlappingWith(const _Rectangle<T>& other) const
		{
			return right > other.left && left < other.right
				&& bottom > other.top && top < other.bottom;
		}
		bool IsContainedBy(const _Rectangle<T>& other) const
		{
			return left >= other.left && right <= other.right &&
				top >= other.top && bottom <= other.bottom;
		}
		bool Contains(const Vector2& point) const
		{
			return point.x >= left && point.x < right&& point.y >= top && point.y < bottom;
		}
		static _Rectangle<T> FromCenter(const Vector2& center, T halfWidth, T halfHeight)
		{
			const Vector2 half((float)halfWidth, (float)halfHeight);
			return _Rectangle<T>(center - half, center + half);
		}
		_Rectangle<T> GetExpanded(T offset) const
		{
			return _Rectangle(left - offset, right + offset, top - offset, bottom + offset);
		}
		Vector2 GetCenter() const 
		{
			return Vector2( (float)(left + right) / 2.0f , (float)(top + bottom) / 2.0f );
		}

		T GetWidth() { return right - left; }
		T GetHeight() { return bottom - top; }

	public:
		T left;
		T right;
		T top;
		T bottom;
	};


	typedef _Rectangle<float> Rectangle;
	typedef _Rectangle<int> RectangleI;
}
