/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 17:43:58 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "adjacency_list.h"
#include "visualizer.h"
#include "SDL.h"

int		read_input(t_graph *graph);

int		enter_reading_loop(t_graph *graph)
{
	SDL_Window		*window;
	t_textures		textures;

	window = SDL_CreateWindow("Lem-in visualizer", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if (!window)
		return (-1);
	textures.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!textures.renderer || init_textures(&textures) < 0)
	{
		SDL_DestroyWindow(window);
		return (-1);
	}
	while (1)
	{
		draw_graph(graph, &textures);
		SDL_Delay(1000);
	}
	SDL_DestroyRenderer(textures.renderer);
	SDL_DestroyWindow(window);
	return (0);
}

int		main(int argc, char **argv)
{
	t_graph *graph;

	(void)argc;
	(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	if (read_input(graph) >= 0)
		enter_reading_loop(graph);
	SDL_Quit();
	return (0);
}
