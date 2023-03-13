#include "chk_soft_renderer.h"
#include "chk_opengl.h"
#include "../common/chk_colors.h"

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
		// Resize the render target
		auto target_size = m_internal_resolution;
		auto size_changed = false;
		if (!m_internal_resolution_set)
		{
			target_size = m_window.fb_size();
			if (m_window.fb_size_changed())
			{
				dbg::print("Internal resolution is NOT set and changed!");
				size_changed = true;
			}
		}
		else
		{
			if (m_internal_resolution.x != m_last_internal_resolution.x || m_internal_resolution.y != m_last_internal_resolution.y)
			{
				dbg::print("Internal resolution is set and changed!");
				size_changed = true;
				m_last_internal_resolution = m_internal_resolution;
			}
		}

		if (size_changed && !m_window.is_minimized())
		{
			m_render_target.resize(target_size);
		}

		// Set the viewport
		opengl::update_viewport(m_gl, {0, 0}, m_window.fb_size());

		// Clear the render target
		// m_render_target.clear(colors::packed_rgba(clear_color()));
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

	void SoftRenderer::set_internal_resolution(ivec2 resolution)
	{
		dbg::print("Locking internal resolution to {}", resolution);
		m_internal_resolution_set = true;
		m_internal_resolution = resolution;
	}

	void SoftRenderer::reset_internal_resolution()
	{
		dbg::print("Unlocking internal resolution");
		m_internal_resolution_set = false;
	}

	// Rendering
	void SoftRenderer::draw_line(LineCommand *command)
	{
		// Variables
		int x0 = command->p0.x;
		int y0 = command->p0.y;
		int x1 = command->p1.x;
		int y1 = command->p1.y;
		int width = m_render_target.w();
		int height = m_render_target.h();
		uint32_t color = colors::packed_rgba(command->color.r, command->color.g, command->color.b, command->color.a);

		// Clip line endpoints to buffer boundaries
		if (x0 < 0 || x0 >= width || y0 < 0 || y0 >= height || x1 < 0 || x1 >= width || y1 < 0 || y1 >= height)
		{
			// Line is completely outside buffer, return without drawing anything
			return;
		}
		if (x0 < 0)
		{
			y0 += (y1 - y0) * (-x0) / (x1 - x0);
			x0 = 0;
		}
		if (y0 < 0)
		{
			x0 += (x1 - x0) * (-y0) / (y1 - y0);
			y0 = 0;
		}
		if (x1 >= width)
		{
			y1 -= (y1 - y0) * (x1 - width + 1) / (x1 - x0);
			x1 = width - 1;
		}
		if (y1 >= height)
		{
			x1 -= (x1 - x0) * (y1 - height + 1) / (y1 - y0);
			y1 = height - 1;
		}

		// Bresenham algorithm
		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;
		int err = dx - dy;

		auto buffer = m_render_target.memory();
		while (true)
		{
			int index = (y0 * width + x0) * 4;
			auto pixel = reinterpret_cast<uint32_t *>(buffer + index);
			*pixel = color;

			if (x0 == x1 && y0 == y1)
			{
				break;
			}

			int e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				x0 += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				y0 += sy;
			}
		}
	}

	void SoftRenderer::draw_triangle(TriangleCommand *command) { dbg::print("Drawing triangle at {}, {}, {}", command->p0, command->p1, command->p2); }
	void SoftRenderer::draw_rect(RectCommand *command) { dbg::print("Drawing rect at {} of size {}", command->pos, command->size); }
	void SoftRenderer::draw_quad(QuadCommand *command) { dbg::print("Drawing quad at {}, {}, {}, {}", command->p0, command->p1, command->p2, command->p3); }
	void SoftRenderer::draw_circle(CircleCommand *command) { dbg::print("Drawing circle at {} of radius {}", command->p, command->r); }
	void SoftRenderer::draw_ellipse(EllipseCommand *command) { dbg::print("Drawing ellipse between {} and {}", command->p0, command->p1); }
}