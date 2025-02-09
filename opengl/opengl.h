#ifndef OPENGL_H
# define OPENGL_H

/*	API:
 *		Windowing
 * */

void	*opengl_window(unsigned w, unsigned h, const char *t);
int		opengl_window_should_close(void *wnd);
int		opengl_window_close(void *wnd);
int		opengl_window_poll_events(void *wnd);
int		opengl_window_swap_buffers(void *wnd);
int		opengl_window_get_screen_w(void *wnd);
int		opengl_window_get_screen_h(void *wnd);

/*	API:
 *		Renderer
 * */

void	*opengl_renderer(void *wnd);
int		opengl_renderer_begin(void *rndr);
int		opengl_renderer_end(void *rndr);
int		opengl_renderer_close(void *rndr);
int		opengl_renderer_get_shader(void *rndr);
int		opengl_renderer_set_shader(void *rndr, unsigned id);
int		opengl_renderer_get_vao(void *rndr);
int		opengl_renderer_set_vao(void *rndr, unsigned id);
int		opengl_renderer_get_vbo(void *rndr);
int		opengl_renderer_set_vbo(void *rndr, unsigned id);
int		opengl_renderer_get_ebo(void *rndr);
int		opengl_renderer_set_ebo(void *rndr, unsigned id);
int		opengl_renderer_get_texture(void *rndr);
int		opengl_renderer_set_texture(void *rndr, unsigned id);
int		opengl_renderer_get_default_texture(void *rndr);
int		opengl_renderer_set_default_texture(void *rndr, unsigned id);
int		opengl_renderer_get_quad_count(void *rndr);
int		opengl_renderer_set_quad_count(void *rndr, unsigned c);
int		opengl_renderer_get_quad_max(void *rndr);

/*	API:
 *		Draw
 * */

int	opengl_draw_rect(void *rndr, float rec[4], float col[4]);
int	opengl_draw_rect_ex(void *rndr, float rec[4], float col[4], float off[2], float rot);
int	opengl_draw_texture(void *rndr, float rec[4], float col[4], unsigned id);
int	opengl_draw_texture_ex(void *rndr, float rec[4], float col[4], float uv[4], float off[2], float rot, unsigned id);
int	opengl_draw_font(void *rndr, void *font, const char *text, float pos[2], float siz, float col[4]);

/*	API:
 *		Texture
 * */

int	opengl_texture(int w, int h, void *dat);
int	opengl_texture_load(const char *path);
int	opengl_texture_siz(unsigned id, float dst[2]);
int	opengl_texture_del(unsigned id);

/*	API:
 *		Font
 * */

void	*opengl_font(const char *path, unsigned glyph_count, unsigned siz);
int		opengl_font_unload(void *font);
int		opengl_font_texture(void *font);
int		opengl_font_siz(void *font, int glyph, float dst[2]);
int		opengl_font_uv(void *font, int glyph, float dst[4]);
int		opengl_font_advance(void *font, int glyph, float dst[2]);
int		opengl_font_glyph_count(void *font);
int		opengl_font_measure(void *font, const char *text, unsigned siz, float dst[2]);

int	opengl_shader(const char **glsl_vert, const char **glsl_frag);
int	opengl_clear(float r, float g, float b, float a);

#endif
