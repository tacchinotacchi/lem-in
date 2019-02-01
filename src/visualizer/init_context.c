/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:29:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/01 13:18:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include "ft_printf.h"

int		sdl_set_attr()
{
	if ( SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0
		|| SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0
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

int		init_main_buffers(t_renderer *renderer)
{
	glGenBuffers(1, &renderer->node_buffer);
	glGenBuffers(1, &renderer->edge_buffer);
	glGenVertexArrays(1, &renderer->node_vao);
	return (0);
}

int		setup_gl(t_renderer *renderer)
{
	GLenum	err;

	err = glewInit();
	if (err != GLEW_OK)
		ft_dprintf(2, "Glew failed: %s\n", glewGetErrorString(err));
	if (init_textures(renderer) < 0)
		return (-1);
	if (init_shaders(renderer) < 0)
		return (-1);
	if (init_main_buffers(renderer) < 0)
		return (-1);
	return (0);
}
