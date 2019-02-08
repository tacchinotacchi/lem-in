/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:22:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 15:57:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H
# include "adjacency_list.h"
# include "lem_in.h"
# include <GL/glew.h>
# include <SDL.h>
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
	GLuint			ant_program;
	GLuint			node_texture;
	GLuint			start_texture;
	GLuint			end_texture;
	GLuint			edge_texture;
	GLuint			ant_texture;
	GLuint			node_vao;
	GLuint			ant_vao;
	GLuint			node_buffer;
	GLuint			edge_buffer;
	GLuint			ant_buffer;
	t_array			node_coords;
	t_array			edge_indices;
	t_array			ant_data;
	t_view			view;
	float			animation_time;
	uint64_t		last_frame_time;
	uint64_t		msec_waited;
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

int				acquire_context(t_visualizer *vis, t_renderer *renderer);
int				sdl_set_attr();
int				setup_gl(t_renderer *renderer);
int				init_textures(t_renderer *renderer);
int				init_shaders(t_renderer *renderer);
int				init_any_shader(GLuint *id, GLenum shader_type,
					const char *filename);
int				check_link_error(GLuint *id, const char *message);
void			matrix_add(float *dst, float *a, float *b);
void			matrix_sub(float *dst, float *a, float *b);
void			matrix_mul(float *dst, float *a, float *b);
void			matrix_identity(float *mat);
void			matrix_add_movement(float *mat, float *direction);
void			matrix_add_rotation(float *mat, float y_axis, float x_axis);
void			matrix_perspective(float *mat, float near_clip, float far_clip,
					float fov);
void			execute_line(t_lemin *info, t_renderer *renderer, char animate);
void			handle_event(const SDL_Event *event, t_lemin *info,
					t_visualizer *vis, t_renderer *renderer);
void			update_position(t_view *view);
void			rotate_vector(float *v, float v_rotation, float r_rotation);
void			convert_input(t_lemin *info, t_renderer *renderer);
void			generate_coords(t_lemin *info, t_visualizer *vis);
void			update_equilibrium(t_graph *graph, t_visualizer *vis);
void			draw_graph(t_lemin *info, t_renderer *renderer);
int				enter_reading_loop(t_lemin *info, t_visualizer *vis,
					t_renderer *renderer);
void			transform_matrices_set(t_renderer *renderer, GLuint program);

#endif
