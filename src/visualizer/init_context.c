/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:29:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 18:49:49 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"

int		sdl_set_attr()
{
	if ( SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0
		|| SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2) < 0
		|| SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0
		|| SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) < 0)
		return (-1);
	return (0);
}

int		acquire_context(t_visualizer *vis, t_renderer *renderer)
{
	renderer->ctx = SDL_GL_CreateContext(vis->window);
	if (!renderer->ctx)
		return (-1);
	return (0);
}

int		setup_gl(t_renderer *renderer)
{
	if (init_textures(renderer) < 0)
		return (-1);
	if (init_shaders(renderer) < 0)
		return (-1);
	return (0);
}
