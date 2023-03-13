#pragma once

#include "../common/chk_common.h"
#include "../common/chk_math.h"

#include <vector>

namespace chk
{
	class Bitmap
	{
	public:
		Bitmap(const ivec2 &size) { resize(size); }
		~Bitmap();

		CHK_NON_COPYABLE(Bitmap);

		// Helpers
		void resize(const ivec2 &size);
		void clear();

		// Getters
		int w() const { return m_size.x; }
		int h() const { return m_size.y; }
		ivec2 size() const { return m_size; }
		size_t stride() const { return m_stride; }
		size_t bpp() const { return m_bpp; }

		size_t memory_size() const { return m_stride * m_size.y * sizeof(*m_memory); }
		uint8_t *memory() const { return m_memory; }

	private:
		ivec2 m_size;
		uint8_t *m_memory{nullptr};
		size_t m_stride{0};
		size_t m_bpp{4};
	};
}