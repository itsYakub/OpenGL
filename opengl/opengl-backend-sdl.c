#include "opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include "glad/gl.h"
#include "SDL3/SDL.h"

typedef struct s_wnd {
	void	*ptr;
	void	*ctx;
	int		exit;
}	t_wnd;

void	*opengl_window(unsigned w, unsigned h, const char *t) {
	int		_glad_version;
	t_wnd	*_wnd;
	
	/* Initializing the backend (SDL2) */
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		return (0);
	}
	/* Setting up the OpenGL attributes */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	/* Creating the window object */
	_wnd = (t_wnd *) calloc(1, sizeof(t_wnd));
	/* Creating the SDL window */
	_wnd->ptr = SDL_CreateWindow(t, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (!_wnd->ptr) {
		SDL_Quit();
		return (NULL);
	}
	/* Creating the SDL OpenGL context */
	_wnd->ctx = SDL_GL_CreateContext(_wnd->ptr);
	if (!_wnd->ctx) {
		SDL_DestroyWindow(_wnd->ptr);
		SDL_Quit();
		return (NULL);
	}
	SDL_GL_MakeCurrent(_wnd->ptr, _wnd->ctx);
	/* Loading OpenGL via glad */
	_glad_version = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
	/* Setting up OpenGL viewport */
	glViewport(0, 0, w, h);
	/* Setting up the exit flag */
	_wnd->exit = 0;
	/* Log info to stdout */
	fprintf(stdout, "INFO.: Backend : SDL %i.%i.%i\n", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION);
	fprintf(stdout, "INFO.: Graphics API : OpenGL %i.%i\n", GLAD_VERSION_MAJOR(_glad_version), GLAD_VERSION_MINOR(_glad_version));
	return (_wnd);
}

int	opengl_should_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	return (_wnd->exit);
}

int	opengl_close(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	SDL_GL_DestroyContext(_wnd->ctx);
	SDL_DestroyWindow(_wnd->ptr);
	SDL_free(_wnd);
	SDL_Quit();
	return (1);
}

int	opengl_poll_events(void *wnd) {
	SDL_Event	_event;
	t_wnd		*_wnd;

	_wnd = (t_wnd *) wnd;
	while (SDL_PollEvent(&_event)) {
		switch (_event.type) {
			case (SDL_EVENT_QUIT): {
				_wnd->exit = 1;
			} break;
		}
	}
	return (1);
}

int	opengl_swap_buffers(void *wnd) {
	t_wnd	*_wnd;

	_wnd = (t_wnd *) wnd;
	SDL_GL_SwapWindow(_wnd->ptr);
	return (1);
}

int	opengl_get_screen_w(void *wnd) {	
	t_wnd	*_wnd;
	int		_w;
	int		_h;

	_wnd = (t_wnd *) wnd;
	SDL_GetWindowSize(_wnd->ptr, &_w, &_h);
	return (_w);
}

int	opengl_get_screen_h(void *wnd) {
	t_wnd	*_wnd;
	int		_w;
	int		_h;

	_wnd = (t_wnd *) wnd;
	SDL_GetWindowSize(_wnd->ptr, &_w, &_h);
	return (_h);
}
