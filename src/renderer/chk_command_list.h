#pragma once

#include "../common/chk_common.h"
#include "../common/chk_math.h"

#include <memory>
#include <vector>

namespace chk
{
	enum class GraphicsCommandKind
	{
		Line,
		Triangle,
		Rect,
		Quad,
		Circle,
		Ellipse
	};

	struct GraphicsCommand
	{
		GraphicsCommand(const GraphicsCommandKind &kind, const vec4 &color = {1, 1, 1, 1}) : kind{kind}, color{color} {}
		virtual ~GraphicsCommand() {}

		GraphicsCommandKind kind;
		vec4 color;
	};

	struct LineCommand : GraphicsCommand
	{
		LineCommand(const vec2 &p0, const vec2 &p1, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Line, color}, p0{p0}, p1{p1} {}
		~LineCommand() = default;

		vec2 p0, p1;
	};

	struct TriangleCommand : GraphicsCommand
	{
		TriangleCommand(const vec2 &p0, const vec2 &p1, const vec2 &p2, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Triangle, color}, p0{p0}, p1{p1}, p2{p2} {}
		~TriangleCommand() = default;

		vec2 p0, p1, p2;
	};

	struct RectCommand : GraphicsCommand
	{
		RectCommand(const vec2 &pos, const vec2 &size, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Rect, color}, pos{pos}, size{size} {}
		~RectCommand() = default;

		vec2 pos, size;
	};

	struct QuadCommand : GraphicsCommand
	{
		QuadCommand(const vec2 &p0, const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Quad, color}, p0{p0}, p1{p1}, p2{p2}, p3{p3} {}
		~QuadCommand() = default;

		vec2 p0, p1, p2, p3;
	};

	struct CircleCommand : GraphicsCommand
	{
		CircleCommand(const vec2 &p, float r, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Circle, color}, p{p}, r{r} {}
		~CircleCommand() = default;

		vec2 p;
		float r;
	};

	struct EllipseCommand : GraphicsCommand
	{
		EllipseCommand(const vec2 &p0, const vec2 &p1, const vec4 &color = {1, 1, 1, 1})
			: GraphicsCommand{GraphicsCommandKind::Ellipse, color}, p0{p0}, p1{p1} {}
		~EllipseCommand() = default;

		vec2 p0, p1;
	};

	class CommandList
	{
	public:
		CommandList() = default;
		~CommandList() = default;
		CHK_NON_COPYABLE_NON_MOVABLE(CommandList);

		void push_line(const vec2 &p0, const vec2 &p1, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<LineCommand>(p0, p1, c)); }
		void push_triangle(const vec2 &p0, const vec2 &p1, const vec2 &p2, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<TriangleCommand>(p0, p1, p2, c)); }
		void push_rect(const vec2 &pos, const vec2 &size, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<RectCommand>(pos, size, c)); }
		void push_quad(const vec2 &p0, const vec2 &p1, const vec2 &p2, const vec2 &p3, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<QuadCommand>(p0, p1, p2, p3, c)); }
		void push_circle(const vec2 &p, float r, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<CircleCommand>(p, r, c)); }
		void push_circle(const vec2 &p0, const vec2 &p1, const vec4 c = {1, 1, 1, 1}) { m_commands.emplace_back(std::make_unique<EllipseCommand>(p0, p1, c)); }

		void clear() { m_commands.clear(); }
		size_t size() const { return m_commands.size(); }

		// Iterators
		inline auto begin() { return m_commands.begin(); }
		inline auto end() { return m_commands.end(); }
		inline auto rbegin() { return m_commands.rbegin(); }
		inline auto rend() { return m_commands.rend(); }

		// Const Iterators
		inline const auto begin() const { return m_commands.begin(); }
		inline const auto end() const { return m_commands.end(); }
		inline const auto rbegin() const { return m_commands.rbegin(); }
		inline const auto rend() const { return m_commands.rend(); }

	private:
		std::vector<std::unique_ptr<GraphicsCommand>> m_commands;
	};
}