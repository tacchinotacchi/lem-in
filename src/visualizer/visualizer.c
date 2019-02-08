/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 17:26:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "adjacency_list.h"
#include "visualizer.h"
#include "parser.h"
#include "lem_in.h"
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

int		main(int argc, char **argv)
{
	t_lemin			input;
	t_visualizer	vis;
	t_renderer		renderer;

	(void)argc;
	(void)argv;
	ft_bzero(&input, sizeof(t_lemin));
	parse_input(&input, L_ANTS | L_COMMENT | L_COMMAND | L_INSTRUCTION);
	generate_coords(&input, &vis);
	init_ants(&input);
	if (init_sdl(&vis, &renderer) < 0)
	{
		ft_dprintf(2, "Failed to acquire context: %s\n", SDL_GetError());
		return (0);
	}
	else if (setup_gl(&renderer))
		return (0);
	else
	{
		srand(SDL_GetTicks());
		enter_reading_loop(&input, &vis, &renderer);
	}
	free_resources(&vis, &renderer);
	free_lemin(&input);
	return (0);
}
