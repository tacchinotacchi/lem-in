/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:28:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 02:55:46 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	init_data(t_renderer *renderer)
{
	ft_bzero(&renderer->view, sizeof(t_view));
	array_init(&renderer->node_coords, sizeof(float[3]));
	array_init(&renderer->edge_indices, sizeof(GLuint[2]));
	array_init(&renderer->ant_data, sizeof(GLuint[2]));
	renderer->animation_time = 1.f;
	matrix_perspective(renderer->view.perspective_mat, 0.1f, 200.f, 0.9f);
	renderer->last_frame_time = SDL_GetTicks();
}

static void	update_shader_data(t_lemin *info, t_renderer *renderer)
{
	uint64_t	curr_time;

	curr_time = SDL_GetTicks();
	renderer->animation_time += (float)(curr_time - renderer->last_frame_time +
		renderer->msec_waited) * 0.001f;
	if (renderer->animation_time > 1.f)
		renderer->animation_time = 1.f;
	convert_input(info, renderer);
	matrix_identity(renderer->view.rotation_mat);
	matrix_add_rotation(renderer->view.rotation_mat,
		renderer->view.v_rotation, renderer->view.r_rotation);
	matrix_identity(renderer->view.transform_mat);
	matrix_add_movement(renderer->view.transform_mat, renderer->view.position);
}

static void	sync_frame(t_renderer *renderer)
{
	uint64_t	curr_time;

	curr_time = SDL_GetTicks();
	if (curr_time - renderer->last_frame_time < 17)
	{
		SDL_Delay(17 - (curr_time - renderer->last_frame_time));
		renderer->msec_waited =
			17 - (curr_time - renderer->last_frame_time);
	}
}

int			enter_reading_loop(t_lemin *info, t_visualizer *vis,
				t_renderer *renderer)
{
	int			quit;

	quit = 0;
	init_data(renderer);
	while (!quit)
	{
		while (SDL_PollEvent(&vis->event) != 0)
		{
			if (vis->event.type == SDL_QUIT)
				quit = 1;
			handle_event(&vis->event, info, vis, renderer);
		}
		update_position(&renderer->view);
		update_equilibrium(&info->graph, vis);
		update_shader_data(info, renderer);
		draw_graph(info, renderer);
		sync_frame(renderer);
		SDL_GL_SwapWindow(vis->window);
		renderer->last_frame_time = SDL_GetTicks();
	}
	return (0);
}
