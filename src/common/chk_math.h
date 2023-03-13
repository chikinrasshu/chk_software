#pragma once

#include "chk_common.h"
#include "chk_dbg.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

// Typedef common math types
namespace chk
{
	typedef glm::ivec2 ivec2;
	typedef glm::ivec3 ivec3;
	typedef glm::ivec4 ivec4;

	typedef glm::dvec2 dvec2;
	typedef glm::dvec3 dvec3;
	typedef glm::dvec4 dvec4;

	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;
}

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

// Common math operations
namespace chk
{
	vec2 scale_keep_aspect(vec2 src, vec2 dst);
}