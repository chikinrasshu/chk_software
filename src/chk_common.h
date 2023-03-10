#pragma once

#include <format>
#include <string>
#include <string_view>
#include <source_location>

namespace chk {

	namespace dbg {
		void print(std::string_view sender, std::string_view msg, const std::source_location location = std::source_location::current());
		void print_args(std::string_view sender, std::string_view format, std::format_args args, const std::source_location location = std::source_location::current());

		void log(std::string_view msg, const std::source_location location = std::source_location::current());
		void warn(std::string_view msg, const std::source_location location = std::source_location::current());
		void error(std::string_view msg, const std::source_location location = std::source_location::current());

		template <typename... Ts> void log(std::string_view sender, const std::format_string<Ts...> format, Ts&&... args, const std::source_location location = std::source_location::current()) { chk::dbg::print_args("  LOG  ", format, std::make_format_args(args...), location); }
		template <typename... Ts> void warn(std::string_view sender, const std::format_string<Ts...> format, Ts&&... args, const std::source_location location = std::source_location::current()) { chk::dbg::print_args("WARNING", format, std::make_format_args(args...), location); }
		template <typename... Ts> void error(std::string_view sender, const std::format_string<Ts...> format, Ts&&... args, const std::source_location location = std::source_location::current()) { chk::dbg::print_args("ERROR", format, std::make_format_args(args...), location); }
	}
}