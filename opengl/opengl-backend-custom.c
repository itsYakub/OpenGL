#include "opengl.h"

#include <stdlib.h>

/*	This file provides you with all the ready-to-use template for implementing
 *	Your own custom backend. Feel free to expand upon this file and use whatever tech
 *	you want to use (i.e. RGFW, Allegro5, DirectX, bare X11 or Wayland, you name it!)
 *	~ itsYakub
 * */

typedef struct s_wnd {
	/* Your implementation here */
}	t_wnd;

void	*opengl_window(unsigned w, unsigned h, const char *t) {
	t_wnd	*_wnd;
	
	_wnd = (t_wnd *) calloc(1, sizeof(t_wnd));
	return (_wnd);
}

int	opengl_should_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	return (1);
}

int	opengl_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	free(_wnd);
	return (1);
}

int	opengl_poll_events(void *wnd) {
	t_wnd		*_wnd;

	_wnd = (t_wnd *) wnd;
	return (1);
}

int	opengl_swap_buffers(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	return (1);
}

int	opengl_get_screen_w(void *wnd) {	
	t_wnd	*_wnd;
	
	_wnd = (t_wnd *) wnd;
	return (1);
}

int	opengl_get_screen_h(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	return (1);
}
