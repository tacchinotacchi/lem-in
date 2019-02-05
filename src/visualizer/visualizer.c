/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/05 01:44:35 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "adjacency_list.h"
#include "visualizer.h"
#include "parser.h"
#include "lem-in.h"
#include "ft_printf.h"
#include <SDL.h>

int		init_sdl(t_visualizer *vis, t_renderer *renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (-1);
	else
	{
		if (sdl_set_attr() < 0)
			return (-1);
		vis->window = SDL_CreateWindow("Lem-in visualizer",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 1000, 1000,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (vis->window == NULL)
			return (-1);
		else if (acquire_context(vis, renderer) < 0)
			return (-1);
	}
	return (0);
}

void	free_resources(t_visualizer *vis, t_renderer *renderer)
{
	array_clear(&renderer->node_coords, NULL);
	array_clear(&renderer->edge_indices, NULL);
	free(vis->adj_matrix);
	vis->adj_matrix = NULL;
	SDL_DestroyWindow(vis->window);
	vis->window = NULL;
	SDL_Quit();
}

int		enter_reading_loop(t_lemin *info, t_visualizer *vis, t_renderer *renderer)
{
	int				quit;

	quit = 0;
	ft_bzero(&renderer->view, sizeof(t_view));
	array_init(&renderer->ant_coords, sizeof(float[3]));
	array_init(&renderer->node_coords, sizeof(float[3]));
	array_init(&renderer->edge_indices, sizeof(GLuint[2]));
	matrix_perspective(renderer->view.perspective_mat, 0.1f, 200.f, 0.9f);
	while (!quit)
	{
		while(SDL_PollEvent(&vis->event) != 0)
		{
			if (vis->event.type == SDL_QUIT)
				quit = 1;
			handle_event(&vis->event, &renderer->view);
		}
		update_position(&renderer->view);
		update_equilibrium(&info->graph, vis);
		convert_input(info, renderer);
		matrix_identity(renderer->view.rotation_mat);
		matrix_add_rotation(renderer->view.rotation_mat,
			renderer->view.v_rotation, renderer->view.r_rotation);
		matrix_identity(renderer->view.transform_mat);
		matrix_add_movement(renderer->view.transform_mat, renderer->view.position);
		draw_graph(renderer);
		SDL_GL_SwapWindow(vis->window);
		/* TODO decent fps limiter */
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_lemin 		input;
	t_visualizer	vis;
	t_renderer		renderer;

	(void)argc;
	(void)argv;
	ft_bzero(&input, sizeof(t_lemin));
	parse_input(&input, L_ANTS | L_COMMENT | L_COMMAND | L_INSTRUCTION);
	generate_coords(&input, &vis);
	if (init_sdl(&vis, &renderer) < 0)
	{
		ft_dprintf(2, "Failed to acquire context: %s\n", SDL_GetError());
		return (0);
	}
	else if (setup_gl(&renderer))
		return (0);
	else
		enter_reading_loop(&input, &vis, &renderer);
	free_resources(&vis, &renderer);
	/*free_all(input); free_all lem-in inputs*/
	return (0);
}
