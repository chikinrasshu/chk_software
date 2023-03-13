#include "chk_path.h"
#include "chk_dbg.h"

#include <whereami.h>

#include <filesystem>

namespace chk
{
    namespace path
    {
        static std::string g_to_exe = "";
        static fmt::string_view g_to_exe_dir;
        static fmt::string_view g_exe_name;

        void internal_get_to_exe()
        {
            int dirname_length;
            int length = wai_getExecutablePath(nullptr, 0, &dirname_length);
            g_to_exe.resize(length + 1);
            int written = wai_getExecutablePath(g_to_exe.data(), static_cast<int>(g_to_exe.size()), &dirname_length);
            g_to_exe[length] = '\0';

            g_to_exe_dir = {g_to_exe.data(), static_cast<size_t>(dirname_length + 1)};
            g_exe_name = {g_to_exe.data() + dirname_length + 1, static_cast<size_t>(length - dirname_length - 1)};

            dbg::print("The path to the exe is: {} and the filename is {}", g_to_exe_dir, g_to_exe.substr(dirname_length + 1, length - dirname_length));
        }

        std::string to_exe()
        {
            if (g_to_exe.empty())
            {
                internal_get_to_exe();
            }

            return g_to_exe;
        }

        std::string to_file(const std::string &rel_to_exe)
        {
            if (g_to_exe.empty())
            {
                internal_get_to_exe();
            }

            auto result = std::filesystem::path(g_to_exe_dir.begin(), g_to_exe_dir.end());
            result += rel_to_exe;
            return std::filesystem::weakly_canonical(result).string();
        }
    }
}