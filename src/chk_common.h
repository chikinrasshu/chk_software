#pragma once

#include <format>
#include <string>
#include <string_view>
#include <source_location>
#include <stdexcept>

namespace chk {

	namespace dbg {
		struct log_format_string {
			std::string_view str;
			std::source_location loc;

			log_format_string(const char* str, const std::source_location& loc = std::source_location::current()) : str(str), loc(loc) {}
		};

		void internal_log(const std::string_view sender, const log_format_string& format, std::format_args args);
		std::string internal_fmt(const std::string_view sender, const log_format_string& format, std::format_args args);
		void internal_error_print(const std::string_view msg);

		template<typename... Ts> void log(const std::string_view sender, const log_format_string& format, Ts&&... args) { internal_log(sender, format, std::make_format_args(args...)); }
		template<typename... Ts> void print(const log_format_string& format, Ts&&... args) { internal_log("  LOG  ", format, std::make_format_args(args...)); }
		template<typename... Ts> void warn(const log_format_string& format, Ts&&... args) { internal_log("WARNING", format, std::make_format_args(args...)); }
		template<typename... Ts> void error(const log_format_string& format, Ts&&... args) { auto msg = internal_fmt(" ERROR ", format, std::make_format_args(args...)); internal_error_print(msg); throw std::runtime_error(msg); }
	}
}