#include "chk_window.h"
#include <GLFW/glfw3.h>

namespace chk
{
	static int g_internal_window_count = 0;
	void internal_register_window() { if (!g_internal_window_count) { if (!glfwInit()) { dbg::error("Failed to initialize GLFW!"); } } ++g_internal_window_count; }
	void internal_release_window() { --g_internal_window_count; if (!g_internal_window_count) { glfwTerminate(); } else if (g_internal_window_count < 0) { dbg::error("Releasing a window when there are {} registered!", g_internal_window_count); } }

	Window::Window(const glm::ivec2& size, const std::string& caption) {
		internal_register_window();
		m_handle = glfwCreateWindow(size.x, size.y, caption.data(), nullptr, nullptr);
		if (!m_handle) { dbg::error("Failed to create the main window!"); internal_release_window(); }

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

		m_is_running = true;
	}

	Window::~Window() { if (m_handle) { internal_release_window(); m_handle = nullptr; } }

	bool Window::run(chk::callback frame_cb) {
		m_frame_cb = frame_cb;

		glfwSetTime(0.0);
		m_current_time = m_last_time = glfwGetTime();
		while (!glfwWindowShouldClose(m_handle)) {
			glfwPollEvents();
			m_current_time = glfwGetTime();
			m_delta_time = m_current_time - m_last_time;
			m_last_time = m_current_time;

			if (!is_running()) { return false; }
			if (m_frame_cb) { m_frame_cb(); }
		}

		return is_running();
	}

	// GLFW Callbacks
#define CHK_GET_WIN auto win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle))
	void Window::s_cb_keyfun(GLFWwindow* handle, int key, int scancode, int action, int mods) {}
	void Window::s_cb_charfun(GLFWwindow* handle, unsigned int codepoint) {}
	void Window::s_cb_charmodsfun(GLFWwindow* handle, unsigned int codepoint, int mods) {}
	void Window::s_cb_dropfun(GLFWwindow* handle, int path_count, const char** paths) {}
	void Window::s_cb_cursorposfun(GLFWwindow* handle, double xpos, double ypos) {}
	void Window::s_cb_cursorenterfun(GLFWwindow* handle, int entered) {}
	void Window::s_cb_mousebuttonfun(GLFWwindow* handle, int button, int action, int mods) {}
	void Window::s_cb_scrollfun(GLFWwindow* handle, double dx, double dy) {}
	void Window::s_cb_windowposfun(GLFWwindow* handle, int x, int y) { CHK_GET_WIN; win->m_pos = { x, y }; }
	void Window::s_cb_windowsizefun(GLFWwindow* handle, int width, int height) { CHK_GET_WIN; win->m_size = { width, height }; }
	void Window::s_cb_framebuffersizefun(GLFWwindow* handle, int width, int height) { CHK_GET_WIN; win->m_fb_size = { width, height }; }
	void Window::s_cb_windowrefreshfun(GLFWwindow* handle) { CHK_GET_WIN; if (win->m_frame_cb) { win->m_frame_cb(); } }
	void Window::s_cb_windowclosefun(GLFWwindow* handle) { CHK_GET_WIN; win->m_is_running = false; }
	void Window::s_cb_windowiconifyfun(GLFWwindow* handle, int minimized) { CHK_GET_WIN; win->m_is_minimized = !!(minimized); }
	void Window::s_cb_windowmaximizefun(GLFWwindow* handle, int maximized) { CHK_GET_WIN; win->m_is_maximized = !!(maximized); }
	void Window::s_cb_windowfocusfun(GLFWwindow* handle, int focused) { CHK_GET_WIN; win->m_is_focused = !!(focused); }
	void Window::s_cb_windowcontentscalefun(GLFWwindow* handle, float dpi_x, float dpi_y) { CHK_GET_WIN; win->m_dpi = { dpi_x, dpi_y }; }
#undef CHK_GET_WIN
}