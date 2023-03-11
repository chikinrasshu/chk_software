#include "chk_software.h"

using namespace chk;

int main()
{
	auto window = Window({800, 600}, "chk_software renderer");
	auto command_list = CommandList();

	return window.run(
		[&window, &command_list]()
		{
			if (window.size_changed())
			{
				dbg::print("Size changed to {}", window.size());
			}

			command_list.clear();

			command_list.push_line({5, 7}, {16, 3}, colors::pink);
			command_list.push_rect({32, 7}, {8, 12}, colors::red);
		});
}
