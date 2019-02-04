/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:18 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/03 23:23:43 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static int		texture_from_file(GLuint *id, const char *filename)
{
	SDL_Surface	*surface;

	surface = SDL_LoadBMP(filename);
	if (!surface)
		return (-1);
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	glTexImage2D(GL_TEXTURE_2D, 0,
		(surface->format->BitsPerPixel == 32) ? GL_RGBA : GL_RGB,
		surface->w, surface->h,
		0 /*TODO this value must be 0 ;) */,
		(surface->format->BitsPerPixel == 32) ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, surface->pixels);
	SDL_FreeSurface(surface);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	return (0);
}

int		init_textures(t_renderer *renderer)
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
	return (0);
}
