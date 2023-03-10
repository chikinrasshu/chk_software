#include "chk_software.h"

int main()
{
	auto window = chk::Window({ 800, 600 }, "chk_software renderer");

	return window.run();
}
