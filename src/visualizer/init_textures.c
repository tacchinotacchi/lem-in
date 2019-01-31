/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:18 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 18:49:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		texture_from_file(t_renderer *renderer, GLuint *id, const char *filename)
{
	SDL_Surface	*surface;

	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);
	surface = SDL_LoadBMP(filename);
	if (!surface)
		return (-1);
	glTexImage2D(GL_TEXTURE_2D, 0,
		(surface->format->BitsPerPixel == 4) ? GL_RGBA : GL_RGB,
		surface->w, surface->h,
		0 /*TODO this value must be 0 ;) */,
		(surface->format->BitsPerPixel == 4) ? GL_RGBA : GL_RGB,
		GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return (0);
}

int		init_textures(t_renderer *renderer)
{
	if (texture_from_file(renderer, &renderer->node_texture,
		"resources/node.bmp") < 0)
		return (-1);
	if (texture_from_file(renderer, &renderer->node_texture,
		"resources/start.bmp") < 0)
		return (-1);
	if (texture_from_file(renderer, &renderer->node_texture,
		"resources/end.bmp") < 0)
		return (-1);
	return (0);
}
