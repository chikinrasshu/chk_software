#include "chk_software.h"

using namespace chk;

int main()
{
	auto window = Window({ 800, 600 }, "chk_software renderer");

	return window.run(
		[&window](){
			if (window.size_changed()) {
				dbg::print("Size changed to {}", window.size());
			}
		});
}
