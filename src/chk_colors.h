#pragma once

#include "chk_common.h"
#include "chk_math.h"

namespace chk {
	namespace colors {
		constexpr glm::vec4 rgba(float r, float g, float b, float a = 255.0f) { return glm::vec4{ r / 255.0f ,g / 255.0f,b / 255.0f,a / 255.0f }; }

		extern glm::vec4 black;
		extern glm::vec4 dark_gray;
		extern glm::vec4 red;
		extern glm::vec4 blue;
		extern glm::vec4 green;
		extern glm::vec4 brown;
		extern glm::vec4 purple;
		extern glm::vec4 light_gray;
		extern glm::vec4 light_green;
		extern glm::vec4 light_blue;
		extern glm::vec4 cyan;
		extern glm::vec4 orange;
		extern glm::vec4 yellow;
		extern glm::vec4 tan;
		extern glm::vec4 pink;
		extern glm::vec4 white;
	}
}
