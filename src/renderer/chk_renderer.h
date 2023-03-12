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

	protected:
		Window &m_window;
	};
}
