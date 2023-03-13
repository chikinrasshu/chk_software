#include "chk_opengl.h"
#include "../common/chk_dbg.h"

namespace chk
{
	namespace opengl
	{

		const char *vert_shader_source = R""""(
			#version 410 core
			layout (location = 0) in vec2 position;
			layout (location = 1) in vec2 texCoord;
			out vec2 fragTexCoord;

			void main()
			{
				gl_Position = vec4(position, 0.0, 1.0);
				fragTexCoord = texCoord;
			}
		)"""";

		const char *frag_shader_source = R""""(
			#version 410 core
			uniform sampler2D tex;
			in vec2 fragTexCoord;
			out vec4 fragColor;

			void main()
			{
				vec3 uvdebug = vec3(fragTexCoord, 0);
				fragColor = vec4(texture(tex, fragTexCoord).rgb + 0.1*uvdebug, 1);
			}
		)"""";

		constexpr GLfloat fs_side = 1.0f;
		static const GLfloat fs_quad_vertices[] = {
			-fs_side, -fs_side,
			fs_side, -fs_side,
			-fs_side, fs_side,
			fs_side, fs_side};

		static const GLfloat fs_quad_tex_coords[] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f};

		void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
		{

			auto src_name = "Unknown";
			switch (source)
			{
			case GL_DEBUG_SOURCE_API:
				src_name = "API";
				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
				src_name = "Window System";
				break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER:
				src_name = "Shader Compiler";
				break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:
				src_name = "Third Party";
				break;
			case GL_DEBUG_SOURCE_APPLICATION:
				src_name = "Application";
				break;
			case GL_DEBUG_SOURCE_OTHER:
				src_name = "Other";
				break;
			}

			auto type_name = "Unknown";
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR:
				type_name = "Error";
				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
				type_name = "Deprecated Behaviour";
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
				type_name = "Undefined Behaviour";
				break;
			case GL_DEBUG_TYPE_PORTABILITY:
				type_name = "Portability";
				break;
			case GL_DEBUG_TYPE_PERFORMANCE:
				type_name = "Performance";
				break;
			case GL_DEBUG_TYPE_MARKER:
				type_name = "Marker";
				break;
			case GL_DEBUG_TYPE_PUSH_GROUP:
				type_name = "Push Group";
				break;
			case GL_DEBUG_TYPE_POP_GROUP:
				type_name = "Pop Group";
				break;
			case GL_DEBUG_TYPE_OTHER:
				type_name = "Other";
				break;
			}

			auto severity_name = "Unknown";
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				severity_name = "High";
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
				severity_name = "Medium";
				break;
			case GL_DEBUG_SEVERITY_LOW:
				severity_name = "Low";
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				severity_name = "Notification";
				break;
			}

			dbg::log("OPEN_GL", "Source: {}, Type: {}, Severity: {} =>", src_name, type_name, severity_name);
			dbg::log("OPEN_GL", "\t - {}", fmt::string_view(reinterpret_cast<const char *>(message), static_cast<size_t>(length)));
		}

		void check_shader_compilation(GLuint shader)
		{
			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				GLchar info_log[512];
				glGetShaderInfoLog(shader, static_cast<GLsizei>(std::size(info_log)), nullptr, info_log);

				dbg::error("Vertex shader compilation failed: {}", info_log);
			}
		}

		void check_shader_linking(GLuint program)
		{
			GLint success;
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				GLchar info_log[512];
				glGetProgramInfoLog(program, static_cast<GLsizei>(std::size(info_log)), nullptr, info_log);

				dbg::error("Shader program linking failed: {}", info_log);
			}
		}

		OpenGL setup()
		{
			auto gl = OpenGL{};

			// - Setup the debug callback
			if (GLAD_GL_ARB_debug_output)
			{
				glEnable(GL_DEBUG_OUTPUT);
				glDebugMessageCallback(debug_callback, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
			}

			// - Setup the fixed pipeline
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

			// - Create the VAO and the VBOs
			glGenVertexArrays(1, &gl.vao);
			glBindVertexArray(gl.vao);

			// - Vertex Buffer Object
			glGenBuffers(static_cast<GLsizei>(std::size(gl.vbos)), gl.vbos);
			glBindBuffer(GL_ARRAY_BUFFER, gl.vbos[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(fs_quad_vertices), fs_quad_vertices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, gl.vbos[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(fs_quad_tex_coords), fs_quad_tex_coords, GL_STATIC_DRAW);

			// - Sending the Vertex Data
			glBindBuffer(GL_ARRAY_BUFFER, gl.vbos[0]);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, gl.vbos[1]);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
			glEnableVertexAttribArray(1);

			// - Texture bindings
			glGenTextures(1, &gl.texture);
			glBindTexture(GL_TEXTURE_2D, gl.texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			// - Create the shader program
			gl.shader_program = glCreateProgram();

			// - Compile the vertex shader
			gl.vert_shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(gl.vert_shader, 1, &vert_shader_source, nullptr);
			glCompileShader(gl.vert_shader);
			check_shader_compilation(gl.vert_shader);

			// - Compile the fragment shader
			gl.frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(gl.frag_shader, 1, &frag_shader_source, nullptr);
			glCompileShader(gl.frag_shader);
			check_shader_compilation(gl.frag_shader);

			//  - Link both shaders with the program
			glAttachShader(gl.shader_program, gl.vert_shader);
			glAttachShader(gl.shader_program, gl.frag_shader);
			glLinkProgram(gl.shader_program);
			check_shader_linking(gl.shader_program);

			//  - We're done.
			glUseProgram(gl.shader_program);

			gl.texture_location = glGetUniformLocation(gl.shader_program, "tex");
			gl.texture_unit = 0;

			return gl;
		}

		void update_viewport(OpenGL &gl, const ivec2 &pos, const ivec2 &size)
		{
			glViewport(pos.x, pos.y, size.x, size.y);
		}

		void update_tex(OpenGL &gl, const Bitmap &bitmap)
		{
			glActiveTexture(GL_TEXTURE0 + gl.texture_unit);
			glBindTexture(GL_TEXTURE_2D, gl.texture);

			// glPixelStorei(GL_PACK_ALIGNMENT, 1);
			// glPixelStorei(GL_UNPACK_ROW_LENGTH, bitmap.stride());

			auto format = GL_RGBA;
			if (bitmap.bpp() != 4)
				dbg::error("Unsupported bitmap bpp of {}!", bitmap.bpp());

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.w(), bitmap.h(), 0, format, GL_UNSIGNED_BYTE, reinterpret_cast<const void *>(bitmap.memory()));
		}

		void draw(OpenGL &gl, const Bitmap &bitmap)
		{
			if (!gl.shader_program)
				dbg::warn("Missing shader program!");

			update_tex(gl, bitmap);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(gl.shader_program);

			glActiveTexture(GL_TEXTURE0 + gl.texture_unit);
			glBindTexture(GL_TEXTURE_2D, gl.texture);
			glUniform1i(gl.texture_location, gl.texture_unit);

			glBindVertexArray(gl.vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}
}