#pragma once

#include "chk_common.h"
#include "chk_dbg.h"

#include <glm/vec2.hpp>

// Include printing helpers for (i,d)vec(2,3,4)
template <glm::length_t L, typename T, enum glm::qualifier Q>
struct fmt::formatter<glm::vec<L, T, Q>>
{
	template <typename ParseContext>
	constexpr auto parse(ParseContext &ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(glm::vec<L, T, Q> const &v, FormatContext &ctx)
	{
		auto &&out = ctx.out();
		fmt::format_to(out, "[{}", v[0]);
		for (glm::length_t i = 1; i < L; ++i)
		{
			fmt::format_to(out, ", {}", v[i]);
		}
		return fmt::format_to(out, "]");
	}
};