#include "opengl.h"

#include <stdlib.h>
#include "glad/gl.h"
#include "cglm/cglm.h"

int	__opengl_draw_quad(void *rndr, float v0[3], float v1[3], float v2[3], float v3[3], float col[4], float uv[4], unsigned id) {
	float	dat[] = {
		v0[0], v0[1], v0[2],		col[0], col[1], col[2], col[3],		uv[0], uv[1],
		v1[0], v1[1], v1[2],		col[0], col[1], col[2], col[3],		uv[2], uv[1],
		v2[0], v2[1], v2[2],		col[0], col[1], col[2], col[3],		uv[0], uv[3],
		v3[0], v3[1], v3[2],		col[0], col[1], col[2], col[3],		uv[2], uv[3],
	};

	if (opengl_renderer_get_quad_count(rndr) >= opengl_renderer_get_quad_max(rndr) || opengl_renderer_get_texture(rndr) != id) {
		opengl_renderer_end(rndr);
		opengl_renderer_set_texture(rndr, id);
		opengl_renderer_begin(rndr);
	}
	glBindVertexArray(opengl_renderer_get_vao(rndr));
	glBindBuffer(GL_ARRAY_BUFFER, opengl_renderer_get_vbo(rndr));
	glBufferSubData(GL_ARRAY_BUFFER, opengl_renderer_get_quad_count(rndr) * 9 * 4 * sizeof(float), sizeof(dat), dat);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	opengl_renderer_set_quad_count(rndr, opengl_renderer_get_quad_count(rndr) + 1);
	return (1);
}

int	opengl_draw_rect(void *rndr, float rec[4], float col[4]) {
	return (opengl_draw_rect_ex(rndr, rec, col, (float [2]) { 0 }, 0.0f));
}

int	opengl_draw_rect_ex(void *rndr, float rec[4], float col[4], float off[2], float rot) {
	unsigned	id;
	float		v0[3];
	float		v1[3];
	float		v2[3];
	float		v3[3];

	id = opengl_renderer_get_default_texture(rndr);
	if (rot == 0.0f) {
		v0[0] = rec[0] - off[0];
		v0[1] = rec[1] - off[1];
		v0[2] = 0.0f;
		v1[0] = rec[0] - off[0] + rec[2];
		v1[1] = rec[1] - off[1];
		v1[2] = 0.0f;
		v2[0] = rec[0] - off[0];
		v2[1] = rec[1] - off[1] + rec[3];
		v2[2] = 0.0f;
		v3[0] = rec[0] - off[0] + rec[2];
		v3[1] = rec[1] - off[1] + rec[3];
		v3[2] = 0.0f;
	}
	else {
		float	d[2];
		float	r[2];

		r[0] = sinf(glm_rad(rot));
		r[1] = cosf(glm_rad(rot));
		d[0] = off[0] * -1.0f;
		d[1] = off[1] * -1.0f;

		v0[0] = rec[0] + d[0] * r[1] - d[1] * r[0];
		v0[1] = rec[1] + d[0] * r[0] + d[1] * r[1];
		v0[2] = 0.0f;

		v1[0] = rec[0] + (d[0] + rec[2]) * r[1] - d[1] * r[0];
		v1[1] = rec[1] + (d[0] + rec[2]) * r[0] + d[1] * r[1];
		v1[2] = 0.0f;
		
		v2[0] = rec[0] + d[0] * r[1] - (d[1] + rec[3]) * r[0];
		v2[1] = rec[1] + d[0] * r[0] + (d[1] + rec[3]) * r[1];
		v2[2] = 0.0f;
		
		v3[0] = rec[0] + (d[0] + rec[2]) * r[1] - (d[1] + rec[3]) * r[0];
		v3[1] = rec[1] + (d[0] + rec[2]) * r[0] + (d[1] + rec[3]) * r[1];
		v3[2] = 0.0f;
	}
	return (__opengl_draw_quad(rndr, v0, v1, v2, v3, col, (float [4]) { 0.0f, 0.0f, 1.0f, 1.0f }, id));
}

int	opengl_draw_texture(void *rndr, float rec[4], float col[4], unsigned id) {
	return (opengl_draw_texture_ex(rndr, rec, col, (float [4]) { 0.0f, 0.0f, 1.0f, 1.0f }, (float [2]) { 0 }, 0.0f, id));
}

int	opengl_draw_texture_ex(void *rndr, float rec[4], float col[4], float uv[4], float off[2], float rot, unsigned id) {
	float	v0[3];
	float	v1[3];
	float	v2[3];
	float	v3[3];

	if (rot == 0.0f) {
		v0[0] = rec[0] - off[0];
		v0[1] = rec[1] - off[1];
		v0[2] = 0.0f;
		v1[0] = rec[0] - off[0] + rec[2];
		v1[1] = rec[1] - off[1];
		v1[2] = 0.0f;
		v2[0] = rec[0] - off[0];
		v2[1] = rec[1] - off[1] + rec[3];
		v2[2] = 0.0f;
		v3[0] = rec[0] - off[0] + rec[2];
		v3[1] = rec[1] - off[1] + rec[3];
		v3[2] = 0.0f;
	}
	else {
		float	d[2];
		float	r[2];

		r[0] = sinf(glm_rad(rot));
		r[1] = cosf(glm_rad(rot));
		d[0] = off[0] * -1.0f;
		d[1] = off[1] * -1.0f;

		v0[0] = rec[0] + d[0] * r[1] - d[1] * r[0];
		v0[1] = rec[1] + d[0] * r[0] + d[1] * r[1];
		v0[2] = 0.0f;

		v1[0] = rec[0] + (d[0] + rec[2]) * r[1] - d[1] * r[0];
		v1[1] = rec[1] + (d[0] + rec[2]) * r[0] + d[1] * r[1];
		v1[2] = 0.0f;
		
		v2[0] = rec[0] + d[0] * r[1] - (d[1] + rec[3]) * r[0];
		v2[1] = rec[1] + d[0] * r[0] + (d[1] + rec[3]) * r[1];
		v2[2] = 0.0f;
		
		v3[0] = rec[0] + (d[0] + rec[2]) * r[1] - (d[1] + rec[3]) * r[0];
		v3[1] = rec[1] + (d[0] + rec[2]) * r[0] + (d[1] + rec[3]) * r[1];
		v3[2] = 0.0f;
	}
	return (__opengl_draw_quad(rndr, v0, v1, v2, v3, col, (float [4]) { 0.0f, 0.0f, 1.0f, 1.0f }, id));
}
