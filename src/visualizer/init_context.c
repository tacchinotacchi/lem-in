/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:29:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/01 12:08:35 by aamadori         ###   ########.fr       */
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
	glBindBuffer(GL_ARRAY_BUFFER, renderer->node_buffer);
	glBufferData(GL_ARRAY_BUFFER, renderer->node_coords.length * sizeof(float),
		renderer->node_coords.ptr, GL_DYNAMIC_DRAW);
	glGenBuffers(1, &renderer->edge_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->edge_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		renderer->edge_vao.length * sizeof(int),
		renderer->edge_vao.ptr, GL_DYNAMIC_DRAW);
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
