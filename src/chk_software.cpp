#include "chk_software.h"

using namespace chk;

int main()
{
	auto window = Window({800, 600}, "chk_software renderer");
	auto renderer = SoftRenderer(window);
	auto command_list = CommandList();

	return window.run(
		[&window, &renderer, &command_list]()
		{
			renderer.begin_frame();

			command_list.clear();

			command_list.push_line({5, 7}, {16, 3}, colors::pink);
			command_list.push_rect({32, 7}, {8, 12}, colors::red);

			renderer.render(command_list);
			renderer.end_frame();
			renderer.present();
		});
}
