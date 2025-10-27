#include <mediahog/mediahog.h>

int main() {
	mediahog_init(MEIDAHOG_VIDEO);

	mediahog_window* window = mediahog_window_init("window", 500, 500, 200, 200);

	while (mediahog_window_should_close(window) == false) {
		mediahog_pollEvents();
	}

	mediahog_window_free(window);

	mediahog_free();
}
