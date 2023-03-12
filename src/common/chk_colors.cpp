#include "chk_colors.h"

namespace chk {
	namespace colors {
		glm::vec4 black = rgba(0, 0, 0);
		glm::vec4 dark_gray = rgba(87, 87, 87);
		glm::vec4 red = rgba(173, 35, 35);
		glm::vec4 blue = rgba(42, 75, 215);
		glm::vec4 green = rgba(29, 105, 20);
		glm::vec4 brown = rgba(129, 74, 25);
		glm::vec4 purple = rgba(129, 38, 192);
		glm::vec4 light_gray = rgba(160, 160, 160);
		glm::vec4 light_green = rgba(129, 197, 122);
		glm::vec4 light_blue = rgba(157, 175, 255);
		glm::vec4 cyan = rgba(41, 208, 208);
		glm::vec4 orange = rgba(255, 146, 51);
		glm::vec4 yellow = rgba(255, 238, 51);
		glm::vec4 tan = rgba(233, 222, 187);
		glm::vec4 pink = rgba(255, 205, 243);
		glm::vec4 white = rgba(255, 255, 255);


		uint32_t packed_bgra(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			uint32_t rgba = (a << 24) | (r << 16) | (g << 8) | b;
			return rgba;
		}

		uint32_t packed_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
			uint32_t rgba = (a << 24) | (b << 16) | (g << 8) | r;
			return rgba;
		}
	}
}