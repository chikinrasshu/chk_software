#pragma once

#include "../renderer/chk_bitmap.h"
#include "../renderer/chk_renderer.h"
#include "chk_opengl.h"

namespace chk
{
	class SoftRenderer : public Renderer
	{
	public:
		SoftRenderer(Window &window);
		~SoftRenderer() = default;

		CHK_NON_COPYABLE_NON_MOVABLE(SoftRenderer);

		void begin_frame();
		void end_frame();
		void render(CommandList &command_list);
		void present();

		// Rendering
		void draw_line(LineCommand *command);
		void draw_triangle(TriangleCommand *command);
		void draw_rect(RectCommand *command);
		void draw_quad(QuadCommand *command);
		void draw_circle(CircleCommand *command);
		void draw_ellipse(EllipseCommand *command);

	private:
		Bitmap m_render_target;
		opengl::OpenGL m_gl;
	};
}