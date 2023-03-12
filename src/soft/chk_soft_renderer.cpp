#include "chk_soft_renderer.h"
#include "chk_opengl.h"

namespace chk
{
	SoftRenderer::SoftRenderer(Window& window) : Renderer(window), m_render_target(m_window.fb_size()) {
		window.recreate(true);

		// Setup OpenGL for the render target to window blit.
		m_gl = opengl::setup();
	}

	void SoftRenderer::begin_frame() {
		if (m_window.size_changed() || m_window.fb_size_changed()) {
			m_render_target.resize(m_window.fb_size());
			opengl::update_viewport(m_gl, { 0, 0 }, m_window.fb_size());
		}

	}

	void SoftRenderer::end_frame() {

	}

	void SoftRenderer::render(CommandList& command_list) {

	}

	void SoftRenderer::present() {
		

		opengl::draw(m_gl, m_render_target);
		m_window.swap_buffers();
	}
}