#pragma once

#include "../renderer/chk_renderer.h"
#include "../renderer/chk_bitmap.h"
#include "chk_opengl.h"

namespace chk
{
	class SoftRenderer : public Renderer {
	public:
		SoftRenderer(Window& window);
		~SoftRenderer() = default;

		CHK_NON_COPYABLE(SoftRenderer);

		void begin_frame();
		void end_frame();
		void render(CommandList& command_list);
		void present();

	private:
		Bitmap m_render_target;
		opengl::OpenGL m_gl;
	};
}