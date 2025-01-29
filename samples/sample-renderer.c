#include "opengl.h"

int	main(int ac, char **av) {
	void	*wnd;	/* opengl window generic poitner */
	void	*rndr;	/* opengl renderer generic pointer */

	/* Initializing an OpenGL window */
	wnd = opengl_window(800, 600, "OpenGL 4.6 - Hello, window!");
	if (!wnd) {
		return (1);
	}
	/* Initializing an OpenGL renderer */
	rndr = opengl_renderer(wnd);
	if (!rndr) {
		opengl_close(wnd);
		return (2);
	}

	while (!opengl_should_close(wnd)) {
		/* All your rendering code should be placed in between "begin" and "end" functions */
		opengl_renderer_begin(rndr);

			/* Clearing the window to nice, dark color */
			opengl_clear(0.2f, 0.2f, 0.2f, 1.0f);
			/* Rendering a red rectangle in the middle of the screen */
			opengl_draw_rect(rndr, (float [2]) { -0.5f, -0.5f }, (float [2]) { 1.0f, 1.0f }, (float [4]) { 0.8f, 0.1f, 0.1f, 1.0f } );

		opengl_renderer_end(rndr);
		
		/* Displaying the frame buffer onto the screen */
		opengl_swap_buffers(wnd);
		/* Polling the window events */
		opengl_poll_events(wnd);
	}
	
	/* Remember to close the renderer and the window before exit */
	opengl_renderer_close(rndr);
	opengl_close(wnd);

	return (0);
}
