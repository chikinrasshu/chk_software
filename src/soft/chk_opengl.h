#pragma once

#include "../renderer/chk_bitmap.h"

#include <glad/gl.h>

namespace chk
{
	namespace opengl
	{

		struct OpenGL
		{
			GLuint vao;
			GLuint vbos[2];
			GLuint vert_shader, frag_shader, shader_program;

			GLuint texture;
			GLint texture_location, texture_unit;
		};

		OpenGL setup();
		void update_viewport(OpenGL &gl, const glm::ivec2 &pos, const glm::ivec2 &size);
		void update_tex(OpenGL &gl, const Bitmap &bitmap);
		void draw(OpenGL &gl, const Bitmap &bitmap);
	}
}