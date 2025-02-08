#include "opengl.h"

int	main(int ac, char **av) {
	void	*wnd;		/* opengl window generic poitner */
	void	*rndr;		/* opengl renderer generic pointer */
	void	*font;		/* opengl font generic pointer */
	int		texture;	/* opengl texture id */

	/* Initializing an OpenGL window */
	wnd = opengl_window(800, 600, "OpenGL 4.6 - Hello, window!");
	if (!wnd) {
		return (1);
	}
	/* Initializing an OpenGL renderer */
	rndr = opengl_renderer(wnd);
	if (!rndr) {
		opengl_window_close(wnd);
		return (2);
	}
	/* Loading a font */
	font = opengl_font("./font.ttf", 64);
	texture = opengl_texture_load("./texture.png");
	while (!opengl_window_should_close(wnd)) {
		/* All your rendering code should be placed in between "begin" and "end" functions */
		opengl_renderer_begin(rndr);

			/* Clearing the window to nice, dark color */
			opengl_clear(0.2f, 0.2f, 0.2f, 1.0f);
			/* Rendering a string on the screen */
			opengl_draw_font(
					rndr,
					font,
					"Hello, world!", 
					(float [2]) { 
						248.0f, 96.0f 
					},
					1.0f, 4.0f,
					(float [4]) {
						1.0f, 1.0f, 1.0f, 1.0f
					}
				);
			/* Rendering a texture in the middle of the screen */
			opengl_draw_texture_ex(
					rndr, 
					(float [4]) { 
						opengl_window_get_screen_w(wnd) / 2.0f,
						opengl_window_get_screen_h(wnd) / 2.0f,
						256.0f, 256.0f
					}, 
					(float [4]) { 
						1.0f, 1.0f, 1.0f, 1.0f 
					}, 
					(float [4]) {
						0.0f, 0.0f, 1.0f, 1.0f 
					},
					(float [2]) {
						128.0f, 128.0f
					},
					0.0f,
					texture
				);

		opengl_renderer_end(rndr);
		
		/* Displaying the frame buffer onto the screen */
		opengl_window_swap_buffers(wnd);
		/* Polling the window events */
		opengl_window_poll_events(wnd);
	}
	
	/* Remember to close the renderer and the window before exit */
	opengl_font_unload(font);
	opengl_texture_del(texture);
	opengl_renderer_close(rndr);
	opengl_window_close(wnd);

	return (0);
}
