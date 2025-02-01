#include "opengl.h"

#include <stdlib.h>
#include "glad/gl.h"
#include "cglm/cglm.h"

int	opengl_clear(float r, float g, float b, float a) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(r, g, b, a);
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
