/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:22:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 20:04:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H

#include "adjacency_list.h"
#include "lem-in.h"
#include <OpenGL/gl.h>
#include <SDL.h>

typedef struct	s_renderer
{
	SDL_GLContext	*ctx;
	GLuint			node_program;
	GLuint			edge_program;
	GLuint			node_texture;
	GLuint			start_texture;
	GLuint			end_texture;
	GLuint			edge_texture;
}				t_renderer;

typedef struct	s_visualizer
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Event	event;
	int			loop;
}				t_visualizer;

int		acquire_context(t_visualizer *vis, t_renderer *renderer);
int		setup_gl(t_renderer *renderer);
int		init_textures(t_renderer *renderer);
int		init_shaders(t_renderer *renderer);
void	matrix_add(float *dst, float *a, float *b);
void	matrix_sub(float *dst, float *a, float *b);
void	matrix_mul(float *dst, float *a, float *b);

#endif
