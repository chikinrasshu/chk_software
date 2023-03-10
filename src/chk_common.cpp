#include "chk_common.h"

#include <iostream>
#include <vector>

namespace chk {
	namespace dbg {
		void internal_log(const std::string_view sender, const log_format_string& format, std::format_args args) {
			const auto& loc = format.loc;
			std::cout << "[" << sender << "]: " << loc.file_name() << ": " << loc.function_name() << "(" << loc.line() << ") => " << format.str << std::endl;
		}

		std::string internal_fmt(const std::string_view sender, const log_format_string& format, std::format_args args)
		{
			const auto& loc = format.loc;

			std::string fmsg;
			std::vformat_to(std::back_inserter(fmsg), format.str, args);

			std::string msg;
			std::format_to(std::back_inserter(msg), "[{}]: {}: {}({}) => {}\n", sender, loc.file_name(), loc.function_name(), loc.line(), fmsg);
			return msg;
		}

		void internal_error_print(const std::string_view msg) {
			std::cerr << msg;
			std::fflush(stderr);
		}

	}
}