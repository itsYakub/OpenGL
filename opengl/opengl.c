#include "opengl.h"

#include <stdlib.h>
#include "glad/gl.h"

typedef struct s_rndr {
	void	*wnd;

	struct {
		unsigned	vao;
		unsigned	vbo;
		unsigned	shd;
	} gl;

	struct {
		unsigned	cnt;
		unsigned	max;
	} quad;

	struct {
		unsigned	cur;
		unsigned	def;
	} tex;
}	t_rndr;

static const char	*glsl_vert = 
"#version 460 core\n"
"layout (location = 0) in vec3  a_Pos;\n"
"layout (location = 1) in vec4  a_Col;\n"
"layout (location = 2) in vec2  a_TexCoord;\n"
"out vec4 v_Col;\n"
"out vec2 v_TexCoord;\n"
"void main() {\n"
" 	gl_Position = vec4(a_Pos, 1.0f);\n"
"	v_Col = a_Col;\n"
"	v_TexCoord = a_TexCoord;\n"
"}";
    
static const char	*glsl_frag = 
"#version 460 core\n"
"in vec4 v_Col;\n"
"in vec2 v_TexCoord;\n"
"out vec4 f_Col;\n"
"uniform sampler2D u_Texture;\n"
"void main() {\n"
"   f_Col = texture(u_Texture, v_TexCoord) * v_Col;\n"
"}";

int	opengl_clear(float r, float g, float b, float a) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(r, g, b, a);
	return (1);
}

void	*opengl_renderer(void *wnd) {
	unsigned	_tex_data;
	t_rndr		*_rndr;
	
	if (!wnd) {
		return (0);
	}
	_rndr = (t_rndr *) calloc(1, sizeof(t_rndr));
	if (!_rndr) {
		return (0);
	}
	_rndr->wnd = wnd;
	/* Setting up shaders */
	_rndr->gl.shd = opengl_shader(&glsl_vert, &glsl_frag);
	/* Setting up quad rendering settings */
	_rndr->quad.max = 16384;
	_rndr->quad.cnt = 0;
	/* Setting up OpenGL buffers */
	glGenVertexArrays(1, &_rndr->gl.vao);
	glBindVertexArray(_rndr->gl.vao);
	glGenBuffers(1, &_rndr->gl.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _rndr->gl.vbo);
	glBufferData(GL_ARRAY_BUFFER, _rndr->quad.max * 9 * 6 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (0 * sizeof(float)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (7 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/* Setting up texture settings */
	_tex_data = 0xffffffff;
	_rndr->tex.cur = _rndr->tex.def = opengl_tex2d(1, 1, &_tex_data);
	return (_rndr);
}

int		opengl_renderer_begin(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (1);
}

int		opengl_renderer_end(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glUseProgram(_rndr->gl.shd);
	glBindVertexArray(_rndr->gl.vao);
	glBindTextureUnit(0, _rndr->tex.cur);
	glDrawArrays(GL_TRIANGLES, 0, _rndr->quad.cnt * 6);
	glBindTextureUnit(0, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	_rndr->quad.cnt = 0;
	return (1);
}

int		opengl_renderer_close(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &_rndr->tex.def);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &_rndr->gl.vbo);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_rndr->gl.vao);
	glUseProgram(0);
	glDeleteProgram(_rndr->gl.shd);
	free(_rndr);
	return (1);
}

int	opengl_renderer_set_shader(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glUseProgram(0);
	glDeleteProgram(_rndr->gl.shd);
	_rndr->gl.shd = id;
	return (1);
}

int	opengl_renderer_set_vao(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_rndr->gl.vao);
	_rndr->gl.vao = id;
	return (1);
}

int	opengl_renderer_set_vbo(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &_rndr->gl.vbo);
	_rndr->gl.vbo = id;
	return (1);
}

int	opengl_shader(const char **glsl_vert, const char **glsl_frag) {
	int	sh_vert;
	int	sh_frag;
	int	sh_prog;

	sh_vert = glCreateShader(GL_VERTEX_SHADER);
	sh_frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sh_vert, 1, glsl_vert, 0);
	glShaderSource(sh_frag, 1, glsl_frag, 0);
	glCompileShader(sh_vert);
	glCompileShader(sh_frag);

	sh_prog = glCreateProgram();
	glAttachShader(sh_prog, sh_vert);
	glAttachShader(sh_prog, sh_frag);
	glLinkProgram(sh_prog);

	glDeleteShader(sh_vert);
	glDeleteShader(sh_frag);
	return (sh_prog);
}

int	opengl_tex2d(int w, int h, void *dat) {
	unsigned	id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (id);
}

int	opengl_tex2d_del(unsigned id) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &id);
	return (1);
}

int	opengl_draw_rect(void *rndr, float pos[2], float siz[2], float col[4]) {
	t_rndr	*_rndr;
	
	_rndr = (t_rndr *) rndr;
	return (opengl_draw_texture(
				rndr,
				(float [4]) {
					pos[0], pos[1], siz[0], siz[1]
				},
				col,
				(float [4]) {
					0.0f, 0.0f, 1.0f, 1.0f
				},
				_rndr->tex.def
			));
}

int	opengl_draw_texture(void *rndr, float rec[4], float col[4], float uv[4], unsigned id) {
	t_rndr	*_rndr;
	float	vertices[] = {
		rec[0], rec[1], 0.0f,			col[0], col[1], col[2], col[3],		uv[0], uv[1], 
		rec[0] + rec[2], rec[1], 0.0f,	col[0], col[1], col[2], col[3],		uv[2], uv[1], 
		rec[0], rec[1] + rec[3], 0.0f,	col[0],	col[1], col[2], col[3],		uv[0], uv[3], 
		
		rec[0] + rec[2], rec[1], 0.0f,			col[0], col[1], col[2], col[3],		uv[2], uv[1], 
		rec[0], rec[1] + rec[3], 0.0f,			col[0],	col[1], col[2], col[3],		uv[0], uv[3], 
		rec[0] + rec[2], rec[1] + rec[3], 0.0f,	col[0],	col[1], col[2], col[3],		uv[2], uv[3], 
	};
	
	_rndr = (t_rndr *) rndr;
	if (_rndr->quad.cnt >= _rndr->quad.max || _rndr->tex.cur != id) {
		opengl_renderer_end(rndr);
		_rndr->tex.cur = _rndr->tex.def;
		opengl_renderer_begin(rndr);
	}
	glBindVertexArray(_rndr->gl.vao);
	glBindBuffer(GL_ARRAY_BUFFER, _rndr->gl.vbo);
	glBufferSubData(GL_ARRAY_BUFFER, _rndr->quad.cnt++ * 9 * 6 * sizeof(float), sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return (1);

}
