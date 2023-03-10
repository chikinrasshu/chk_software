#include "chk_software.h"

int main()
{
	chk::dbg::log("This is a log");
	chk::dbg::warn("This is an warning!");
	chk::dbg::error("This is an error!");

	return 0;
}
