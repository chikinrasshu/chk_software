#include "chk_software.h"

using namespace chk;

int main()
{
	auto exe_path = path::to_file("xDDD/xdd.txt");
	dbg::print("exe_path is '{}'", exe_path);

	auto window = Window({800, 600}, "chk_software renderer");
	auto renderer = SoftRenderer(window);
	renderer.set_internal_resolution({64, 36});
	auto command_list = CommandList();

	return window.run(
		[&window, &renderer, &command_list]()
		{
			renderer.begin_frame();

			command_list.clear();
			command_list.push_clear(colors::transparent);

			command_list.push_line({5, 7}, {48, 26}, colors::yellow);
			command_list.push_line({16, 4}, {2, 48}, colors::red);
			// command_list.push_rect({32, 7}, {8, 12}, colors::red);

			renderer.render(command_list);
			renderer.end_frame();
			renderer.present();
		});
}
