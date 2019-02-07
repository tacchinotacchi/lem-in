/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:29:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 19:27:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include "ft_printf.h"

int		sdl_set_attr(void)
{
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
			SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG) < 0
		|| SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE) < 0
		|| SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) < 0
		|| SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) < 0
		|| SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0
		|| SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) < 0)
		return (-1);
	return (0);
}

int		acquire_context(t_visualizer *vis, t_renderer *renderer)
{
	renderer->ctx = SDL_GL_CreateContext(vis->window);
	if (!renderer->ctx || SDL_GL_SetSwapInterval(0) < 0)
		return (-1);
	return (0);
}

int		init_main_buffers(t_renderer *renderer)
{
	glGenBuffers(1, &renderer->node_buffer);
	glGenBuffers(1, &renderer->edge_buffer);
	glGenBuffers(1, &renderer->ant_buffer);
	glGenVertexArrays(1, &renderer->node_vao);
	glGenVertexArrays(1, &renderer->ant_vao);
	glBindVertexArray(renderer->node_vao);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->node_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->edge_buffer);
	glBindVertexArray(renderer->ant_vao);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->node_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ant_buffer);
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
