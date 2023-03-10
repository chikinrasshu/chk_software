#pragma once

#include "chk_common.h"

#include <glm/vec2.hpp>
#include <iostream>

// Include printing helpers for (i,d)vec(2,3,4)
template<glm::length_t L, typename T, enum glm::qualifier Q>
struct std::formatter<glm::vec<L, T, Q>> : std::formatter<std::string_view> {
	auto format(const glm::vec<L, T, Q>& v, std::format_context& ctx) {
		std::string temp;
		auto&& out = std::back_inserter(temp);
		std::format_to(out, "[{}", v[0]);
		for (glm::length_t i = 1; i < L; ++i) { std::format_to(out, ", {}", v[i]); }
		std::format_to(out, "]");
		return std::formatter<std::string_view>::format(temp, ctx);
	}
};
