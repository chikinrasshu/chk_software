#include "chk_bitmap.h"
#include "../common/chk_colors.h"

namespace chk
{
	Bitmap::~Bitmap() { if (m_memory) { delete[] m_memory; m_memory = nullptr; } }

	void Bitmap::resize(const glm::ivec2& size) {
		// Only resize the memory if the size actually changed
		bool size_changed = (size.x != m_size.x || size.y != m_size.y) || !m_memory;
		if (!size_changed && m_memory) { return; }

		m_size = size;

		auto bits_per_pixel = 32;
		auto bytes_per_pixel = (bits_per_pixel + 7) / 8;
		m_stride = ((static_cast<size_t>(m_size.x) * bytes_per_pixel + 3) / 4) * 4;

		size_t memory_size = m_stride * m_size.y;
		if (m_memory) {
			delete[] m_memory; 
			m_memory = nullptr;
		}

		m_memory = new uint8_t[memory_size];

		// Draw a debug gradient
		// dbg::print("Drawing debug rect from [0, 0] to {}", m_size);
		uint8_t* row = m_memory;
		for (int y = 0; y < m_size.y; ++y) {
			uint32_t* pixel = reinterpret_cast<uint32_t*>(row);
			for (int x = 0; x < m_size.x; ++x) {
				*pixel++ = colors::packed_rgba(static_cast<uint8_t>(x), static_cast<uint8_t>(y), 0, 255);
			}
			row += m_stride;
		}
	}
}