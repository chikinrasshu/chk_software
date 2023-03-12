#include "chk_window.h"
#include "../common/chk_dbg.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace chk
{
	static int g_internal_window_count = 0;
	void internal_register_window();
	void internal_release_window();

	Window::Window(const glm::ivec2 &size, const std::string &caption, bool uses_opengl)
		: m_size(size), m_fb_size(size), m_caption(caption), m_uses_opengl(uses_opengl)
	{
		internal_register_window();

		if (m_uses_opengl)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		else
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_handle = glfwCreateWindow(size.x, size.y, caption.data(), nullptr, nullptr);
		if (!m_handle)
		{
			dbg::error("Failed to create the main window!");
			internal_release_window();
		}

		glfwSetWindowUserPointer(m_handle, this);
		glfwSetKeyCallback(m_handle, s_cb_keyfun);
		glfwSetCharCallback(m_handle, s_cb_charfun);
		glfwSetCharModsCallback(m_handle, s_cb_charmodsfun);
		glfwSetDropCallback(m_handle, s_cb_dropfun);
		glfwSetCursorPosCallback(m_handle, s_cb_cursorposfun);
		glfwSetCursorEnterCallback(m_handle, s_cb_cursorenterfun);
		glfwSetMouseButtonCallback(m_handle, s_cb_mousebuttonfun);
		glfwSetScrollCallback(m_handle, s_cb_scrollfun);
		glfwSetWindowPosCallback(m_handle, s_cb_windowposfun);
		glfwSetWindowSizeCallback(m_handle, s_cb_windowsizefun);
		glfwSetFramebufferSizeCallback(m_handle, s_cb_framebuffersizefun);
		glfwSetWindowRefreshCallback(m_handle, s_cb_windowrefreshfun);
		glfwSetWindowCloseCallback(m_handle, s_cb_windowclosefun);
		glfwSetWindowIconifyCallback(m_handle, s_cb_windowiconifyfun);
		glfwSetWindowMaximizeCallback(m_handle, s_cb_windowmaximizefun);
		glfwSetWindowFocusCallback(m_handle, s_cb_windowfocusfun);
		glfwSetWindowContentScaleCallback(m_handle, s_cb_windowcontentscalefun);

		glfwGetWindowPos(m_handle, &m_pos.x, &m_pos.y);
		glfwGetWindowSize(m_handle, &m_size.x, &m_size.y);
		glfwGetFramebufferSize(m_handle, &m_fb_size.x, &m_fb_size.y);

		if (m_uses_opengl)
		{
			glfwMakeContextCurrent(m_handle);
			if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress)))
			{
				dbg::error("Failed to initialize OpenGL!");
			}
			else
			{
				dbg::print("Loaded OpenGL");
			}
		}

		m_is_running = true;
	}

	Window::~Window()
	{
		if (m_handle)
		{
			internal_release_window();
			m_handle = nullptr;
		}
	}

	bool Window::recreate(bool uses_opengl)
	{
		try
		{
			glm::ivec2 saved_size = m_size;
			std::string saved_caption = m_caption;

			dbg::print("Recreating the window {} an OpenGL context...", uses_opengl ? "with" : "without");
			this->~Window();
			new (&*this) Window(saved_size, saved_caption, uses_opengl);
			return true;
		}
		catch (const std::exception &e)
		{
			dbg::error("{}", e.what());
		}
	}

	bool Window::show()
	{
		if (!m_handle)
		{
			return false;
		}
		glfwShowWindow(m_handle);
		return true;
	}

	bool Window::run(chk::callback frame_cb)
	{
		m_frame_cb = frame_cb;

		glfwSetTime(0.0);
		m_current_time = m_last_time = glfwGetTime();
		if (!show())
		{
			return false;
		}
		while (!glfwWindowShouldClose(m_handle))
		{
			glfwPollEvents();
			m_current_time = glfwGetTime();
			m_delta_time = (m_current_time - m_last_time) * 1000.0f;
			m_last_time = m_current_time;

			std::string title;
			fmt::format_to(std::back_inserter(title), "{} :: dt: {:.4f} :: fps: {:.2f}", m_caption, m_delta_time, 1000.0f / m_delta_time);

			glfwSetWindowTitle(m_handle, title.c_str());

			if (!is_running())
			{
				return false;
			}
			if (m_frame_cb)
			{
				m_frame_cb();
			}

			m_size_changed = false;
			m_fb_size_changed = false;
			m_pos_changed = false;
			m_dpi_changed = false;
			m_focus_changed = false;
			m_fullscreen_changed = false;
		}

		return is_running();
	}

	bool Window::swap_buffers()
	{
		if (!uses_opengl())
		{
			return false;
		}
		glfwSwapBuffers(m_handle);
		return true;
	}

	// GLFW Callbacks
#define CHK_GET_WIN auto win = reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle))
	void Window::s_cb_keyfun(GLFWwindow *handle, int key, int scancode, int action, int mods)
	{
	}
	void Window::s_cb_charfun(GLFWwindow *handle, unsigned int codepoint) {}
	void Window::s_cb_charmodsfun(GLFWwindow *handle, unsigned int codepoint, int mods) {}
	void Window::s_cb_dropfun(GLFWwindow *handle, int path_count, const char **paths) {}
	void Window::s_cb_cursorposfun(GLFWwindow *handle, double xpos, double ypos) {}
	void Window::s_cb_cursorenterfun(GLFWwindow *handle, int entered) {}
	void Window::s_cb_mousebuttonfun(GLFWwindow *handle, int button, int action, int mods) {}
	void Window::s_cb_scrollfun(GLFWwindow *handle, double dx, double dy) {}
	void Window::s_cb_windowposfun(GLFWwindow *handle, int x, int y)
	{
		CHK_GET_WIN;
		win->m_pos = {x, y};
		win->m_pos_changed = true;
	}
	void Window::s_cb_windowsizefun(GLFWwindow *handle, int width, int height)
	{
		CHK_GET_WIN;
		win->m_size = {width, height};
		win->m_size_changed = true;
	}
	void Window::s_cb_framebuffersizefun(GLFWwindow *handle, int width, int height)
	{
		CHK_GET_WIN;
		win->m_fb_size = {width, height};
		win->m_fb_size_changed = true;
	}
	void Window::s_cb_windowrefreshfun(GLFWwindow *handle)
	{
		CHK_GET_WIN;
		if (win->m_frame_cb)
		{
			win->m_frame_cb();
		}
	}
	void Window::s_cb_windowclosefun(GLFWwindow *handle)
	{
		CHK_GET_WIN;
		win->m_is_running = false;
	}
	void Window::s_cb_windowiconifyfun(GLFWwindow *handle, int minimized)
	{
		CHK_GET_WIN;
		win->m_is_minimized = !!(minimized);
	}
	void Window::s_cb_windowmaximizefun(GLFWwindow *handle, int maximized)
	{
		CHK_GET_WIN;
		win->m_is_maximized = !!(maximized);
	}
	void Window::s_cb_windowfocusfun(GLFWwindow *handle, int focused)
	{
		CHK_GET_WIN;
		win->m_is_focused = !!(focused);
		win->m_focus_changed = true;
	}
	void Window::s_cb_windowcontentscalefun(GLFWwindow *handle, float dpi_x, float dpi_y)
	{
		CHK_GET_WIN;
		win->m_dpi = {dpi_x, dpi_y};
		win->m_dpi_changed = true;
	}
#undef CHK_GET_WIN

	// Internals
	void internal_register_window()
	{
		if (!g_internal_window_count && !glfwInit())
		{
			dbg::error("Failed to initialize GLFW!");
		}
		++g_internal_window_count;
	}

	void internal_release_window()
	{
		--g_internal_window_count;
		if (!g_internal_window_count)
		{
			glfwTerminate();
		}
		else if (g_internal_window_count < 0)
		{
			dbg::error("Releasing a window when there are {} registered!", g_internal_window_count);
		}
	}
}