#include "opengl.h"

#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/gl.h"

int	opengl_texture(int w, int h, void *dat) {
	unsigned	id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	return (id);
}

int	opengl_texture_load(const char *path) {
	stbi_uc		*dat;
	unsigned	id;
	int			w;
	int			h;
	int			ch;

	stbi_set_flip_vertically_on_load(1);
	dat = stbi_load(path, &w, &h, &ch, 0);
	if (!dat) {
		return (0);
	}
	id = opengl_texture(w, h, dat);
	free(dat);
	return (id);
}

int	opengl_texture_del(unsigned id) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &id);
	return (1);
}
