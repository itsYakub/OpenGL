#include "opengl.h"

int	main(int ac, char **av) {
	void	*wnd;	/* opengl window generic poitner */

	/* Initializing an OpenGL window */
	wnd = opengl_window(800, 600, "OpenGL 4.6 - Hello, window!");
	if (!wnd) {
		return (1);
	}

	while (!opengl_window_should_close(wnd)) {
		opengl_clear(0.2f, 0.2f, 0.2f, 1.0f);
		opengl_window_swap_buffers(wnd);
		opengl_window_poll_events(wnd);
	}

	/* Remember to close the renderer and the window before exit */
	opengl_window_close(wnd);

	return (0);
}
