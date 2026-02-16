
#pragma once

#include <cstdint>

class COLOR
{
public:
	uint8_t r, g, b, a;
	uint32_t rgb : 24;

	COLOR(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff);
	COLOR(uint32_t rgb = 0xffffff, uint8_t a = 0xff);
	COLOR darken(float value) const;
};

const COLOR WHITE(0xffffff);
const COLOR GRAY(0xa0a0a0);
const COLOR BLACK(0x000000);