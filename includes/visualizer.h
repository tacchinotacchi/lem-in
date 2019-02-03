/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:22:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/03 11:17:40 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H

#include "adjacency_list.h"
#include "lem-in.h"
#include <GL/glew.h>
#include <SDL.h>

# define PI	3.14159265f

typedef struct	s_view
{
	float	v_rotation;
	float	r_rotation;
	float	velocity[3];
	float	position[3];
	float	transform_mat[16];
	float	rotation_mat[16];
	float	perspective_mat[16];
}				t_view;

typedef struct	s_renderer
{
	SDL_GLContext	*ctx;
	GLuint			node_program;
	GLuint			edge_program;
	GLuint			node_texture;
	GLuint			start_texture;
	GLuint			end_texture;
	GLuint			edge_texture;
	GLuint			node_buffer;
	GLuint			node_vao;
	GLuint			edge_buffer;
	t_array			node_coords;
	t_array			edge_indices;
	t_view			view;
}				t_renderer;

typedef struct	s_visualizer
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Event	event;
	char		*adj_matrix;
	size_t		width;
	int			loop;
}				t_visualizer;

int		acquire_context(t_visualizer *vis, t_renderer *renderer);
int		sdl_set_attr();
int		setup_gl(t_renderer *renderer);
int		init_textures(t_renderer *renderer);
int		init_shaders(t_renderer *renderer);
void	matrix_add(float *dst, float *a, float *b);
void	matrix_sub(float *dst, float *a, float *b);
void	matrix_mul(float *dst, float *a, float *b);
void	matrix_identity(float *mat);
void	matrix_add_movement(float *mat, float *direction);
void	matrix_add_rotation(float *mat, float y_axis, float x_axis);
void	matrix_perspective(float *mat, float near_clip, float far_clip,
			float fov);
void	rotate_vector(float *v, float v_rotation, float r_rotation);
void	convert_input(t_lemin *info, t_renderer *renderer);
void	generate_coords(t_lemin *info, t_visualizer *vis);
void	update_equilibrium(t_graph *graph, t_visualizer *vis);
void	draw_graph(t_renderer *renderer);

#endif
