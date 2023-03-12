#pragma once

#include "../common/chk_common.h"
#include "../common/chk_math.h"

#include <vector>

namespace chk
{
	struct Command {
		explicit Command(const glm::vec4& color = glm::vec4{ 1,1,1,1 }) : color(color) {}
		
		CHK_NON_COPYABLE(Command);

		// Getters
		// glm::vec4 aabb() = 0;

		// Members
		glm::vec4 color;
	};

	struct LineCommand : public Command {
		LineCommand(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color = glm::vec4{ 1,1,1,1 })
			: Command(color), p0(p0), p1(p1) {}

		CHK_NON_COPYABLE(LineCommand);

		// Members
		glm::vec2 p0, p1;
	};

	struct TriangleCommand : public Command {
		TriangleCommand(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color = glm::vec4{ 1,1,1,1 })
			: Command(color), p0(p0), p1(p1), p2(p2) {}

		CHK_NON_COPYABLE(TriangleCommand);

		// Members
		glm::vec2 p0, p1, p2;
	};

	struct QuadCommand : public Command {
		QuadCommand(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec4& color = glm::vec4{ 1,1,1,1 })
			: Command(color), p0(p0), p1(p1), p2(p2), p3(p3) {}

		CHK_NON_COPYABLE(QuadCommand);

		// Members
		glm::vec2 p0, p1, p2, p3;
	};

	struct RectCommand : public Command {
		RectCommand(const glm::vec2& pos, const glm::vec2& size, const glm::vec4 color = glm::vec4{ 1,1,1,1 })
			: Command(color), pos(pos), size(size) {}

		CHK_NON_COPYABLE(RectCommand);

		// Members
		glm::vec2 pos, size;
	};

	class CommandList {
	public:
		CommandList() = default;
		~CommandList() = default;

		CHK_NON_COPYABLE(CommandList);

		// Getters
		inline void clear() { return m_commands.clear(); }
		inline size_t size() { return m_commands.size(); }

		// Commands
		void push_line(const glm::vec2& p0, const glm::vec2& p1, const glm::vec4& color = glm::vec4{ 1,1,1,1 }) { m_commands.emplace_back(LineCommand(p0, p1, color)); }
		void push_triangle(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2, const glm::vec4& color = glm::vec4{ 1,1,1,1 }) { m_commands.emplace_back(TriangleCommand(p0, p1, p2, color)); }
		void push_quad(const glm::vec2 p0, const glm::vec2 p1, const glm::vec2 p2, glm::vec2 p3, const glm::vec4& color = glm::vec4{ 1,1,1,1 }) { m_commands.emplace_back(QuadCommand(p0, p1, p2, p3, color)); }
		void push_rect(const glm::vec2 pos, const glm::vec2 size, const glm::vec4& color = glm::vec4{ 1,1,1,1 }) { m_commands.emplace_back(RectCommand(pos, size, color)); }
		//void push_circle();
		//void push_ellipse();
		//void push_polygon();

	private:
		// Members
		std::vector<Command> m_commands{};
	};
}