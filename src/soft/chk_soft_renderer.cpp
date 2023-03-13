#include "chk_soft_renderer.h"
#include "chk_opengl.h"

namespace chk
{
	SoftRenderer::SoftRenderer(Window &window) : Renderer(window), m_render_target(m_window.fb_size())
	{
		window.recreate(true);

		// Setup OpenGL for the render target to window blit.
		m_gl = opengl::setup();
	}

	void SoftRenderer::begin_frame()
	{
		bool resized = false;
		if ((m_window.size_changed() || m_window.fb_size_changed()) && !m_window.is_minimized())
		{
			auto new_size = m_window.fb_size();
			m_render_target.resize(m_window.fb_size());
			opengl::update_viewport(m_gl, {0, 0}, m_window.fb_size());
			resized = true;
		}

		m_render_target.clear();
	}

	void SoftRenderer::end_frame()
	{
	}

	void SoftRenderer::render(CommandList &command_list)
	{
		// Go though every kind of command, and render them
		for (auto &command : command_list)
		{
			if (!command)
				continue;

			switch (command->kind)
			{
			case GraphicsCommandKind::Line:
				draw_line(dynamic_cast<LineCommand *>(command.get()));
				break;
			case GraphicsCommandKind::Triangle:
				draw_triangle(dynamic_cast<TriangleCommand *>(command.get()));
				break;
			case GraphicsCommandKind::Rect:
				draw_rect(dynamic_cast<RectCommand *>(command.get()));
				break;
			case GraphicsCommandKind::Quad:
				draw_quad(dynamic_cast<QuadCommand *>(command.get()));
				break;
			case GraphicsCommandKind::Circle:
				draw_circle(dynamic_cast<CircleCommand *>(command.get()));
				break;
			case GraphicsCommandKind::Ellipse:
				draw_ellipse(dynamic_cast<EllipseCommand *>(command.get()));
				break;
			}
		}
	}

	void SoftRenderer::present()
	{
		if (m_window.is_minimized())
			return;

		opengl::draw(m_gl, m_render_target);
		m_window.swap_buffers();
	}

	// Rendering
	void SoftRenderer::draw_line(LineCommand *command) { dbg::print("Drawing line from {} to {}", command->p0, command->p1); }
	void SoftRenderer::draw_triangle(TriangleCommand *command) { dbg::print("Drawing triangle at {}, {}, {}", command->p0, command->p1, command->p2); }
	void SoftRenderer::draw_rect(RectCommand *command) { dbg::print("Drawing rect at {} of size {}", command->pos, command->size); }
	void SoftRenderer::draw_quad(QuadCommand *command) { dbg::print("Drawing quad at {}, {}, {}, {}", command->p0, command->p1, command->p2, command->p3); }
	void SoftRenderer::draw_circle(CircleCommand *command) { dbg::print("Drawing circle at {} of radius {}", command->p, command->r); }
	void SoftRenderer::draw_ellipse(EllipseCommand *command) { dbg::print("Drawing ellipse between {} and {}", command->p0, command->p1); }
}