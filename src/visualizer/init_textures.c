/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:18 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 19:39:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

const GLint	g_rgba_swizzle_mask[] = {GL_BLUE, GL_GREEN, GL_RED, GL_ALPHA};
const GLint	g_rgb_swizzle_mask[] = {GL_BLUE, GL_GREEN, GL_RED, GL_ONE};

static int	texture_from_file(GLuint *id, const char *filename)
{
	SDL_Surface	*surface;
	uint8_t		bits;

	surface = SDL_LoadBMP(filename);
	if (!surface)
		return (-1);
	bits = surface->format->BitsPerPixel;
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0,
		(bits == 32) ? GL_RGBA : GL_RGB, surface->w, surface->h, 0,
		(bits == 32) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	SDL_FreeSurface(surface);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA,
		(bits == 32) ? g_rgba_swizzle_mask : g_rgb_swizzle_mask);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return (0);
}

int			init_textures(t_renderer *renderer)
{
	if (texture_from_file(&renderer->node_texture,
		"resources/node.bmp") < 0)
		return (-1);
	if (texture_from_file(&renderer->start_texture,
		"resources/start.bmp") < 0)
		return (-1);
	if (texture_from_file(&renderer->end_texture,
		"resources/end.bmp") < 0)
		return (-1);
	if (texture_from_file(&renderer->edge_texture,
		"resources/edge.bmp") < 0)
		return (-1);
	if (texture_from_file(&renderer->ant_texture,
		"resources/ant.bmp") < 0)
		return (-1);
	return (0);
}
