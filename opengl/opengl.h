#ifndef OPENGL_H
# define OPENGL_H

/*	API:
 *		Windowing
 * */
void	*opengl_window(unsigned w, unsigned h, const char *t);
int		opengl_should_close(void *wnd);
int		opengl_close(void *wnd);
int		opengl_poll_events(void *wnd);
int		opengl_swap_buffers(void *wnd);
int		opengl_get_screen_w(void *wnd);
int		opengl_get_screen_h(void *wnd);

/*	API:
 *		Renderer
 * */
void	*opengl_renderer(void *wnd);
int		opengl_renderer_begin(void *rndr);
int		opengl_renderer_end(void *rndr);
int		opengl_renderer_close(void *rndr);
int		opengl_renderer_set_shader(void *rndr, unsigned id);
int		opengl_renderer_set_vao(void *rndr, unsigned id);
int		opengl_renderer_set_vbo(void *rndr, unsigned id);
int		opengl_clear(float r, float g, float b, float a);

int	opengl_draw_rect(void *rndr, float pos[2], float siz[2], float col[4]);
int	opengl_draw_texture(void *rndr, float rec[4], float col[4], float uv[4], unsigned id);

int	opengl_shader(const char **glsl_vert, const char **glsl_frag);

int	opengl_tex2d(int w, int h, void *dat);
int	opengl_tex2d_del(unsigned id);

#endif
