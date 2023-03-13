#pragma once

#include "chk_common.h"
#include "chk_math.h"

namespace chk
{
	namespace colors
	{
		constexpr vec4 rgba(float r, float g, float b, float a = 255.0f) { return vec4{r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f}; }

		uint32_t packed_bgra(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		uint32_t packed_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

		uint32_t packed_bgra(float r, float g, float b, float a);
		uint32_t packed_rgba(float r, float g, float b, float a);

		uint32_t packed_bgra(vec3 c, float a = 1.0f);
		uint32_t packed_rgba(vec3 c, float a = 1.0f);

		uint32_t packed_bgra(vec4 c);
		uint32_t packed_rgba(vec4 c);

		vec4 unpacked_rgba(uint32_t c);
		vec4 unpacked_bgra(uint32_t c);

		extern vec4 black;
		extern vec4 dark_gray;
		extern vec4 red;
		extern vec4 blue;
		extern vec4 green;
		extern vec4 brown;
		extern vec4 purple;
		extern vec4 light_gray;
		extern vec4 light_green;
		extern vec4 light_blue;
		extern vec4 cyan;
		extern vec4 orange;
		extern vec4 yellow;
		extern vec4 tan;
		extern vec4 pink;
		extern vec4 white;
	}
}
