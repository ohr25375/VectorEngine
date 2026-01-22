#pragma once

#include <cmath>
#include <concepts>
#include <algorithm>

template<typename T>
	requires std::integral<T> || std::floating_point<T>
class VECTOR2
{
public:
	T x, y;
	VECTOR2()
	{
		x = 0;
		y = 0;
	}

	template<typename T2, typename T3>
		requires (std::integral<T2> || std::floating_point<T2>) && (std::integral<T3> || std::floating_point<T3>)
	VECTOR2(const T2 x, const T3 y) : x(x), y(y) {}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2(const T2 xy) : x(xy), y(xy) {}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2(const VECTOR2<T2> xy) : x(xy.x), y(xy.y) {}

	VECTOR2& operator+=(const VECTOR2& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	VECTOR2 operator+(const VECTOR2& rhs) const {
		VECTOR2<T> res = *this;
		res += rhs;
		return res;
	}

	VECTOR2& operator-=(const VECTOR2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	VECTOR2 operator-(const VECTOR2& rhs) const {
		VECTOR2<T> res = *this;
		res -= rhs;
		return res;
	}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2 & operator*=(const T2 & rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2 operator*(const T2 & rhs) const {
		VECTOR2<T> res = *this;
		res *= rhs;
		return res;
	}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2 & operator/=(const T2 & rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	template<typename T2>
		requires std::integral<T2> || std::floating_point<T2>
	VECTOR2 operator/(const T2 & rhs) const {
		VECTOR2<T> res = *this;
		res /= rhs;
		return res;
	}

	VECTOR2<int> round(const uint32_t val = 1) const {
		VECTOR2<int> res;
		res.x = std::round(x / (float)val) * val;
		res.y = std::round(y / (float)val) * val;
		return res;
	}

	VECTOR2 rotate(const double& angle) const {
		VECTOR2<T> res;
		res.x = x * cos(-angle) - y * sin(-angle);
		res.y = x * sin(-angle) + y * cos(-angle);
		return res;
	}

	VECTOR2 scale(const VECTOR2& rhs) const {
		VECTOR2<T> res = *this;
		res.x *= rhs.x;
		res.y *= rhs.y;
		return res;
	}

	T dot(const VECTOR2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double magnitude() const {
		return sqrt(this->dot(*this));
	}

	VECTOR2 normalized() const {
		VECTOR2<T> res = *this;
		if (res.magnitude() == 0) {
			return res;
		}
		res /= res.magnitude();
		return res;
	}

	VECTOR2 clamp(const VECTOR2& min, const VECTOR2& max) const
	{
		VECTOR2<T> res = *this;
		res.x = std::clamp(res.x, min.x, max.x);
		res.y = std::clamp(res.x, min.x, max.y);
		return res;
	}
};

#define VECTOR2i VECTOR2<int>
#define VECTOR2f VECTOR2<float>