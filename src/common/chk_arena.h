#pragma once

#include "chk_common.h"

namespace chk
{
    class ArenaAllocator
    {
    public:
        ArenaAllocator() {}
        ~ArenaAllocator() = default;

    private:
        uint8_t *memory;
    };
}