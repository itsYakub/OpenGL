#include "opengl.h"

#include <stdlib.h>
#include <stdio.h>
#include "glad/gl.h"
#include "ft2build.h"
#include "freetype/freetype.h"

#define MAX(a, b) ( a > b ? a : b )

typedef struct s_glyph {
	unsigned	id;
	unsigned	wid;
	unsigned	hght;
	float		advance[2];
	float		uv[4];
}	t_glyph;

typedef struct s_font {
	t_glyph		*glyphs;
	unsigned	glyph_count;
	unsigned	texture;
}	t_font;

void	*opengl_font(const char *path, unsigned glyph_count, unsigned siz) {
	FT_Library	_ft_lib;
	FT_Face		_ft_face;
	t_font		*_font;
	float		_tex_siz[2];
	float		_tex_pos;
	int			_swizzle_mask[4];

	/* Initializing the freetype library and font face */
	if (FT_Init_FreeType(&_ft_lib)) {
		return (NULL);
	}
	if (FT_New_Face(_ft_lib, path, 0, &_ft_face)) {
		FT_Done_FreeType(_ft_lib);
		return (NULL);		
	}
	FT_Set_Pixel_Sizes(_ft_face, 0, siz);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	/* Getting the size of a texture atlas */
	_tex_siz[0] = 0.0f;
	_tex_siz[1] = 0.0f;
	for (int i = 0; i < glyph_count; i++) {
		if (FT_Load_Char(_ft_face, (char) i, FT_LOAD_RENDER)) {
			continue;
		}
		/* This is a simplified font atlas, going from left to right as a single row */
		_tex_siz[0] += _ft_face->glyph->bitmap.width;
		_tex_siz[1] = MAX(_tex_siz[1], _ft_face->glyph->bitmap.rows);
	}
	_font = (t_font *) calloc(1, sizeof(t_font));
	_font->glyphs = (t_glyph *) calloc(glyph_count, sizeof(t_glyph));
	_font->glyph_count = glyph_count;
	_font->texture = opengl_texture(_tex_siz[0], _tex_siz[1], NULL);
	glBindTexture(GL_TEXTURE_2D, _font->texture);
	/* 
	 *	I want to keep the shader universal, thus I'll remap all the channels of the atlas to a red channel .
	 *	The typical way of loading font is to store them as a single channel in the texture.
	 *	This is generally a correct practice, but it doesn't allow for having a single shader for drawing everything.
	 * */
	_swizzle_mask[0] = GL_RED;
	_swizzle_mask[1] = GL_RED;
	_swizzle_mask[2] = GL_RED;
	_swizzle_mask[3] = GL_RED;
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, _swizzle_mask);
	/* Loading characters and storing them in the atlas */
	_tex_pos = 0.0f;
	for (int i = 0; i < glyph_count; i++) {
		if (FT_Load_Char(_ft_face, (char) i, FT_LOAD_RENDER)) {
			continue;
		}
		/* We retrieve the size of each glyph */
		_font->glyphs[i].wid = _ft_face->glyph->bitmap.width;
		_font->glyphs[i].hght = _ft_face->glyph->bitmap.rows;
		/* We store the uv of each glyph */
		_font->glyphs[i].uv[0] = _tex_pos / _tex_siz[0];
		_font->glyphs[i].uv[1] = _ft_face->glyph->bitmap.rows / _tex_siz[1];
		_font->glyphs[i].uv[2] = (_tex_pos + _ft_face->glyph->bitmap.width) / _tex_siz[0];
		_font->glyphs[i].uv[3] = 0.0f;
		_font->glyphs[i].advance[0] = _ft_face->glyph->advance.x;
		_font->glyphs[i].advance[1] = _ft_face->glyph->advance.x;
		glTexSubImage2D(GL_TEXTURE_2D, 0, (int) _tex_pos, 0, _ft_face->glyph->bitmap.width, _ft_face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, _ft_face->glyph->bitmap.buffer);
		/* We move through the atlas using _tex_pos cursor */
		_tex_pos += _ft_face->glyph->bitmap.width;
	}
	/* Clean-up */
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(_ft_face);
	FT_Done_FreeType(_ft_lib);
	/* Log info to stdout */
	fprintf(stdout, "INFO.: Font name: %s\n", path);
	fprintf(stdout, "INFO.: Font glyph count: %u\n", _font->glyph_count);
	return (_font);
}

int	opengl_font_unload(void *font) {
	t_font	*_font;

	_font = (t_font *) font;
	opengl_texture_del(_font->texture);
	free(_font->glyphs);
	free(_font);
	return (1);
}

int	opengl_font_texture(void *font) {
	t_font	*_font;

	_font = (t_font *) font;
	return (_font->texture);
}

int	opengl_font_siz(void *font, int glyph, float dst[2]) {
	t_font	*_font;

	_font = (t_font *) font;
	 dst[0] = _font->glyphs[glyph].wid;
	 dst[1] = _font->glyphs[glyph].hght;
	return (1);
}

int	opengl_font_advance(void *font, int glyph, float dst[2]) {
	t_font	*_font;

	_font = (t_font *) font;
	dst[0] = (int) _font->glyphs[glyph].advance[0] >> 6;
	dst[1] = (int) _font->glyphs[glyph].advance[1] >> 6;
	return (1);
}

int	opengl_font_uv(void *font, int glyph, float dst[4]) {
	t_font	*_font;

	_font = (t_font *) font;
	if (glyph >= _font->glyph_count) {
		return (0);
	}
	memcpy(dst, _font->glyphs[glyph].uv, sizeof(float) * 4);
	return (1);
}

int		opengl_font_glyph_count(void *font) {
	t_font	*_font;

	_font = (t_font *) font;
	return (_font->glyph_count);	
}

int	opengl_font_measure(void *font, const char *text, unsigned siz, float dst[2]) {
	float	_siz[2];
	float	_adv[2];

	_siz[0] = 0.0f;
	_siz[1] = 0.0f;
	while (*text) {
		opengl_font_advance(font, *text, _adv);
		_siz[0] += ((int) _adv[0]) * siz;
		_siz[1] = ((int) _adv[1]) * siz;
		text++;
	}
	memcpy(dst, _siz, sizeof(float) * 2);
	return (1);
}
