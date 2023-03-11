#include "chk_dbg.h"

namespace chk
{
    namespace dbg
    {

        void internal_log(const fmt::string_view sender, const fmt::string_view format, fmt::format_args &&args)
        {
            fmt::print(stderr, "{}\n", internal_fmt(sender, format, std::forward<fmt::format_args>(args)));
        }

        std::string internal_fmt(const fmt::string_view sender, const fmt::string_view format, fmt::format_args &&args)
        {
            std::string msg;
            fmt::vformat_to(std::back_inserter(msg), format, args);
            return msg;
        }

        void internal_error_print(const fmt::string_view msg)
        {
            fmt::println(stderr, msg);
        }

    }
}