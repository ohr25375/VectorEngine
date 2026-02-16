#include "color.hpp"

COLOR::COLOR(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) : r(r), g(g), b(b), a(a) {
	rgb = (r << 16) + (g << 8) + b;
}

COLOR::COLOR(const uint32_t rgb, const uint8_t a)
{
	r = (rgb & 0xff0000) >> 16;
	g = (rgb & 0x00ff00) >> 8;
	b = (rgb & 0x0000ff);
	this->a = a;
	this->rgb = (r << 16) + (g << 8) + b;
}

COLOR COLOR::darken(const float value) const
{
	COLOR darkened = *this;
	darkened.r *= value;
	darkened.g *= value;
	darkened.b *= value;
	darkened.rgb = (darkened.r << 16) + (darkened.g << 8) + darkened.b;
	return darkened;
}
