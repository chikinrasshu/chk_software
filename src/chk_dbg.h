#pragma once

#include <fmt/core.h>

namespace chk
{
    namespace dbg
    {
        void internal_log(const fmt::string_view sender, const fmt::string_view format, fmt::format_args &&args);
        std::string internal_fmt(const fmt::string_view sender, const fmt::string_view format, fmt::format_args &&args);
        void internal_error_print(const fmt::string_view msg);

        template <typename... Ts>
        void log(const fmt::string_view sender, const fmt::string_view &format, Ts &&...args)
        {
            internal_log(sender, format, fmt::make_format_args(args...));
        }

        template <typename... Ts>
        void print(const fmt::string_view &format, Ts &&...args)
        {
            internal_log("  LOG  ", format, fmt::make_format_args(args...));
        }

        template <typename... Ts>
        void warn(const fmt::string_view &format, Ts &&...args)
        {
            internal_log("WARNING", format, fmt::make_format_args(args...));
        }

        template <typename... Ts>
        void error(const fmt::string_view &format, Ts &&...args)
        {
            auto msg = internal_fmt(" ERROR ", format, fmt::make_format_args(args...));
            internal_error_print(msg);
            throw std::runtime_error(msg);
        }
    }
}