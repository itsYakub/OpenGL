#include "opengl.h"

#include <stdlib.h>
#include "glad/gl.h"
#include "cglm/cam.h"
#include "cglm/mat4.h"

typedef struct s_rndr {
	void	*wnd;

	struct {
		unsigned	vao;
		unsigned	vbo;
		unsigned	ebo;
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
	struct {
		mat4		proj;
		unsigned	proj_uid;
		mat4		view;
		unsigned	view_uid;
	} la;
}	t_rndr;

static const char	*glsl_vert = 
"#version 460 core\n"
"layout (location = 0) in vec3  a_Pos;\n"
"layout (location = 1) in vec4  a_Col;\n"
"layout (location = 2) in vec2  a_TexCoord;\n"
"out vec4 v_Col;\n"
"out vec2 v_TexCoord;\n"
"uniform mat4	u_proj;\n"
"uniform mat4	u_view;\n"
"void main() {\n"
" 	gl_Position = u_proj * u_view * vec4(a_Pos, 1.0f);\n"
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

void	*opengl_renderer(void *wnd) {
	unsigned	_tex_data;
	unsigned	*_indices;
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
	/* Setting up projection matrices */
	glUseProgram(_rndr->gl.shd);
	glm_ortho(0.0f, (float) opengl_window_get_screen_w(wnd), 0.0f, (float) opengl_window_get_screen_h(wnd), -1.0f, 1.0f, _rndr->la.proj);
	glm_mat4_identity(_rndr->la.view);
	_rndr->la.proj_uid = glGetUniformLocation(_rndr->gl.shd, "u_proj");
	_rndr->la.view_uid = glGetUniformLocation(_rndr->gl.shd, "u_view");
	glUseProgram(0);
	/* Setting up quad rendering settings */
	_rndr->quad.max = 16384;
	_rndr->quad.cnt = 0;
	/* Setting up OpenGL buffers */
	_indices = (unsigned *) calloc(_rndr->quad.max * 6, sizeof(unsigned));
	for (int i = 0, off = 0; i < _rndr->quad.max * 6; off += 4) {
		_indices[i++] = 0 + off;
		_indices[i++] = 1 + off;
		_indices[i++] = 2 + off;
		_indices[i++] = 1 + off;
		_indices[i++] = 2 + off;
		_indices[i++] = 3 + off;
	}
	glGenVertexArrays(1, &_rndr->gl.vao);
	glBindVertexArray(_rndr->gl.vao);
	glGenBuffers(1, &_rndr->gl.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _rndr->gl.vbo);
	glBufferData(GL_ARRAY_BUFFER, _rndr->quad.max * 9 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &_rndr->gl.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rndr->gl.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _rndr->quad.max * 6 * sizeof(unsigned), _indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (0 * sizeof(float)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (7 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	free(_indices);
	/* Setting up texture settings */
	_tex_data = 0xffffffff;
	_rndr->tex.cur = _rndr->tex.def = opengl_texture(1, 1, &_tex_data);
	/* Enable alpha-blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	glUniformMatrix4fv(_rndr->la.proj_uid, 1, 0, &_rndr->la.proj[0][0]);
	glUniformMatrix4fv(_rndr->la.view_uid, 1, 0, &_rndr->la.view[0][0]);
	glDrawElements(GL_TRIANGLES, _rndr->quad.cnt * 6, GL_UNSIGNED_INT, 0);
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

int	opengl_renderer_get_shader(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->gl.shd);
}

int	opengl_renderer_set_shader(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glUseProgram(0);
	glDeleteProgram(_rndr->gl.shd);
	_rndr->gl.shd = id;
	return (1);
}

int	opengl_renderer_get_vao(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->gl.vao);

}

int	opengl_renderer_set_vao(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_rndr->gl.vao);
	_rndr->gl.vao = id;
	return (1);
}

int	opengl_renderer_get_vbo(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->gl.vbo);

}

int	opengl_renderer_set_vbo(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &_rndr->gl.shd);
	_rndr->gl.shd = id;
	return (1);
}

int	opengl_renderer_get_ebo(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->gl.ebo);
}

int	opengl_renderer_set_ebo(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &_rndr->gl.shd);
	_rndr->gl.shd = id;
	return (1);
}

int		opengl_renderer_get_texture(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->tex.cur);
}

int		opengl_renderer_set_texture(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	_rndr->tex.cur = id;
	return (1);
}

int	opengl_renderer_get_default_texture(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->tex.def);
}

int	opengl_renderer_set_default_texture(void *rndr, unsigned id) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &_rndr->tex.def);
	_rndr->tex.def = id;
	return (1);
}

int		opengl_renderer_get_quad_count(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->quad.cnt);
}

int		opengl_renderer_set_quad_count(void *rndr, unsigned c) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	_rndr->quad.cnt = c;
	return (1);
}

int		opengl_renderer_get_quad_max(void *rndr) {
	t_rndr	*_rndr;

	_rndr = (t_rndr *) rndr;
	return (_rndr->quad.max);
}
