#pragma once

#include "../common/chk_common.h"
#include "../common/chk_math.h"

#include <functional>

// Forward declare GLFW dependency
struct GLFWwindow;

namespace chk
{
	using callback = std::function<void()>;

	class Window
	{
	public:
		Window(const glm::ivec2 &size, const std::string &caption = "chk_software", bool uses_opengl = false);
		~Window();

		// Non Copyable
		CHK_NON_COPYABLE(Window);

		bool recreate(bool uses_opengl = false);
		bool show();
		bool run(chk::callback frame_cb = nullptr);
		bool swap_buffers();

		[[nodiscard]] bool is_running() const { return m_is_running; }
		[[nodiscard]] bool is_maximized() const { return m_is_maximized; }
		[[nodiscard]] bool is_minimized() const { return m_is_minimized; }
		[[nodiscard]] bool is_focused() const { return m_is_focused; }
		[[nodiscard]] bool is_fullscreen() const { return m_is_fullscreen; }

		[[nodiscard]] bool size_changed() const { return m_size_changed; }
		[[nodiscard]] bool fb_size_changed() const { return m_fb_size_changed; }
		[[nodiscard]] bool pos_changed() const { return m_pos_changed; }
		[[nodiscard]] bool dpi_changed() const { return m_dpi_changed; }
		[[nodiscard]] bool focus_changed() const { return m_focus_changed; }
		[[nodiscard]] bool fullscreen_changed() const { return m_fullscreen_changed; }

		// Position
		[[nodiscard]] int x() const { return m_pos.x; }
		[[nodiscard]] int y() const { return m_pos.y; }
		[[nodiscard]] glm::ivec2 pos() const { return m_pos; }

		// Size
		[[nodiscard]] int w() const { return m_size.x; }
		[[nodiscard]] int h() const { return m_size.y; }
		[[nodiscard]] glm::ivec2 size() const { return m_size; }

		// Framebuffer Size
		[[nodiscard]] int fb_w() const { return m_fb_size.x; }
		[[nodiscard]] int fb_h() const { return m_fb_size.y; }
		[[nodiscard]] glm::vec2 fb_size() const { return m_fb_size; }

		// DPI Scale
		[[nodiscard]] float dpi_x() const { return m_dpi.x; }
		[[nodiscard]] float dpi_y() const { return m_dpi.y; }
		[[nodiscard]] glm::vec2 dpi() const { return m_dpi; }

		// Internals
		[[nodiscard]] GLFWwindow *handle() const { return m_handle; }
		[[nodiscard]] bool uses_opengl() const { return m_uses_opengl; }

	private:
		// State
		bool m_is_running{false};
		bool m_is_maximized{false};
		bool m_is_minimized{false};
		bool m_is_focused{false};
		bool m_is_fullscreen{false};

		// State changes
		bool m_size_changed{false};
		bool m_fb_size_changed{false};
		bool m_pos_changed{false};
		bool m_dpi_changed{false};
		bool m_focus_changed{false};
		bool m_fullscreen_changed{false};

		// Transform
		glm::ivec2 m_pos{0, 0};
		glm::ivec2 m_size{0, 0};
		glm::ivec2 m_fb_size{0, 0};
		glm::vec2 m_dpi{1, 1};

		// Internals
		GLFWwindow *m_handle;
		std::string m_caption;
		callback m_frame_cb{nullptr};
		double m_current_time{0}, m_last_time{0}, m_delta_time{0};
		bool m_uses_opengl{false};

		// Callbacks
		static void s_cb_keyfun(GLFWwindow *handle, int key, int scancode, int action, int mods);
		static void s_cb_charfun(GLFWwindow *handle, unsigned int codepoint);
		static void s_cb_charmodsfun(GLFWwindow *handle, unsigned int codepoint, int mods);
		static void s_cb_dropfun(GLFWwindow *handle, int path_count, const char **paths);
		static void s_cb_cursorposfun(GLFWwindow *handle, double xpos, double ypos);
		static void s_cb_cursorenterfun(GLFWwindow *handle, int entered);
		static void s_cb_mousebuttonfun(GLFWwindow *handle, int button, int action, int mods);
		static void s_cb_scrollfun(GLFWwindow *handle, double dx, double dy);
		static void s_cb_windowposfun(GLFWwindow *handle, int x, int y);
		static void s_cb_windowsizefun(GLFWwindow *handle, int width, int height);
		static void s_cb_framebuffersizefun(GLFWwindow *handle, int width, int height);
		static void s_cb_windowrefreshfun(GLFWwindow *handle);
		static void s_cb_windowclosefun(GLFWwindow *handle);
		static void s_cb_windowiconifyfun(GLFWwindow *handle, int minimized);
		static void s_cb_windowmaximizefun(GLFWwindow *handle, int maximized);
		static void s_cb_windowfocusfun(GLFWwindow *handle, int focused);
		static void s_cb_windowcontentscalefun(GLFWwindow *handle, float dpi_x, float dpi_y);
	};
}