#include "chk_common.h"

#include <iostream>

namespace chk {
	namespace dbg {
		void print(std::string_view sender, std::string_view msg, const std::source_location location) {
			std::cout << "[" << sender << "]: " << location.file_name() << ": " << location.function_name() << "(" << location.line() << ") => " << msg << std::endl;
		}

		void print_args(std::string_view sender, std::string_view format, std::format_args args, const std::source_location location) {
			auto out = std::string();
			std::vformat_to(std::back_inserter(out), format, args);
			chk::dbg::print(sender, out, location);
		}

		void log(std::string_view msg, const std::source_location location) { 
			chk::dbg::print("  LOG  ", msg, location);
		}

		void warn(std::string_view msg, const std::source_location location) { 
			chk::dbg::print("WARNING", msg, location);
		}

		void error(std::string_view msg, const std::source_location location) { 
			chk::dbg::print(" ERROR ", msg, location);
		}
	}
}