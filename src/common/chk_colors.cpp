#include "chk_colors.h"

namespace chk
{
	namespace colors
	{
		vec4 black = rgba(0, 0, 0);
		vec4 dark_gray = rgba(87, 87, 87);
		vec4 red = rgba(173, 35, 35);
		vec4 blue = rgba(42, 75, 215);
		vec4 green = rgba(29, 105, 20);
		vec4 brown = rgba(129, 74, 25);
		vec4 purple = rgba(129, 38, 192);
		vec4 light_gray = rgba(160, 160, 160);
		vec4 light_green = rgba(129, 197, 122);
		vec4 light_blue = rgba(157, 175, 255);
		vec4 cyan = rgba(41, 208, 208);
		vec4 orange = rgba(255, 146, 51);
		vec4 yellow = rgba(255, 238, 51);
		vec4 tan = rgba(233, 222, 187);
		vec4 pink = rgba(255, 205, 243);
		vec4 white = rgba(255, 255, 255);

		uint32_t packed_bgra(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			uint32_t bgra = (a << 24) | (r << 16) | (g << 8) | b;
			return bgra;
		}

		uint32_t packed_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			uint32_t rgba = (a << 24) | (b << 16) | (g << 8) | r;
			return rgba;
		}

		uint32_t packed_bgra(float r, float g, float b, float a)
		{
			return packed_bgra(static_cast<uint8_t>(r / 255.0f),
							   static_cast<uint8_t>(g / 255.0f),
							   static_cast<uint8_t>(b / 255.0f),
							   static_cast<uint8_t>(a / 255.0f));
		}

		uint32_t packed_rgba(float r, float g, float b, float a)
		{
			return packed_rgba(static_cast<uint8_t>(r / 255.0f),
							   static_cast<uint8_t>(g / 255.0f),
							   static_cast<uint8_t>(b / 255.0f),
							   static_cast<uint8_t>(a / 255.0f));
		}

		uint32_t packed_bgra(vec3 c, float a) { return packed_bgra(c.r, c.g, c.b, a); }
		uint32_t packed_rgba(vec3 c, float a) { return packed_rgba(c.r, c.g, c.b, a); }

		uint32_t packed_bgra(vec4 c) { return packed_bgra(c.r, c.g, c.b, c.a); }
		uint32_t packed_rgba(vec4 c) { return packed_rgba(c.r, c.g, c.b, c.a); }

		vec4 unpacked_rgba(uint32_t c)
		{
			// packing => uint32_t rgba = (a << 24) | (b << 16) | (g << 8) | r;
			vec4 result = {((c & 0x000000FF) >> 0),
						   ((c & 0x0000FF00) >> 8),
						   ((c & 0x00FF0000) >> 16),
						   ((c & 0xFF000000) >> 24)};

			return result / 255.0f;
		}

		vec4 unpacked_bgra(uint32_t c)
		{
			// packing => uint32_t bgra = (a << 24) | (r << 16) | (g << 8) | b;
			vec4 result = {((c & 0x00FF0000) >> 16),
						   ((c & 0x0000FF00) >> 8),
						   ((c & 0x000000FF) >> 0),
						   ((c & 0xFF000000) >> 24)};

			return result / 255.0f;
		}
	}
}