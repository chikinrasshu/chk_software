#pragma once

#include "../common/chk_common.h"
#include "../window/chk_window.h"
#include "chk_command_list.h"

namespace chk
{
	class Renderer
	{
	public:
		Renderer(Window &window) : m_window{window} {}
		~Renderer() = default;

		CHK_NON_COPYABLE_NON_MOVABLE(Renderer);

		virtual void begin_frame() = 0;
		virtual void end_frame() = 0;
		virtual void render(CommandList &command_list) = 0;
		virtual void present() = 0;

		virtual void set_internal_resolution(ivec2 resolution) = 0;
		virtual void reset_internal_resolution() = 0;

		void set_clear_color(vec4 &new_clear_color) { m_clear_color = new_clear_color; }
		const vec4 &clear_color() const { return m_clear_color; }

	protected:
		Window &m_window;

		bool m_internal_resolution_set{false};
		ivec2 m_internal_resolution{0, 0};
		ivec2 m_last_internal_resolution{0, 0};

		vec4 m_clear_color{0, 0, 0, 1};
	};
}
