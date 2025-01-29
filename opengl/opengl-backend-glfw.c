#include "opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include "glad/gl.h"
#include "GLFW/glfw3.h"

typedef struct s_wnd {
	void	*ptr;
}	t_wnd;

void	*opengl_window(unsigned w, unsigned h, const char *t) {
	int		_glad_version;
	t_wnd	*_wnd;
	
	/* Initializing GLFW */
	if (!glfwInit()) {
		return (0);
	}
	/* Creating the window object */
	_wnd = (t_wnd *) calloc(1, sizeof(t_wnd));
	/* Creating the GLFW window */
	_wnd->ptr = glfwCreateWindow(w, h, t, 0, 0);
	if (!_wnd->ptr) {
		return (0);
	}
	glfwMakeContextCurrent(_wnd->ptr);
	/* Loading OpenGL via glad */
	_glad_version = gladLoadGL((GLADloadfunc) glfwGetProcAddress);
	/* Setting up OpenGL viewport */
	glViewport(0, 0, w, h);
	/* Log info to stdout */
	fprintf(stdout, "INFO.: Backend : GLFW %i.%i\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
	fprintf(stdout, "INFO.: Graphics API : OpenGL %i.%i\n", GLAD_VERSION_MAJOR(_glad_version), GLAD_VERSION_MINOR(_glad_version));
	return (_wnd);
}

int	opengl_should_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	return (glfwWindowShouldClose(_wnd->ptr));
}

int	opengl_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	glfwDestroyWindow(_wnd->ptr);
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
	glfwSwapBuffers(_wnd->ptr);
	return (1);
}

int	opengl_get_screen_w(void *wnd) {	
	t_wnd	*_wnd;
	int		_w;
	int		_h;

	_wnd = (t_wnd *) wnd;
	glfwGetWindowSize(_wnd->ptr, &_w, &_h);
	return (_w);
}

int	opengl_get_screen_h(void *wnd) {
	t_wnd	*_wnd;
	int		_w;
	int		_h;

	_wnd = (t_wnd *) wnd;
	glfwGetWindowSize(_wnd->ptr, &_w, &_h);
	return (_h);
}
