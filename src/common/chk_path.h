#pragma once
#include "chk_common.h"

namespace chk
{
    namespace path
    {
        std::string to_exe();
        std::string to_file(const std::string &rel_to_exe);
    }
}