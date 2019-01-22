/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 22:11:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "adjacency_list.h"
#include "visualizer.h"
#include "lem-in.h"
#include "SDL.h"

int		enter_reading_loop(t_lemin *input)
{
	SDL_Window		*window;
	t_textures		textures;

	window = SDL_CreateWindow("Lem-in visualizer", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 600, 600, 0);
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
		draw_graph(input, &textures);
		SDL_Delay(1000);
	}
	SDL_DestroyRenderer(textures.renderer);
	SDL_DestroyWindow(window);
	return (0);
}

int		main(int argc, char **argv)
{
	t_lemin input;

	(void)argc;
	(void)argv;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (0);
	ft_bzero(&input, sizeof(t_lemin));
	parse_input(&input);
	enter_reading_loop(&input);
	SDL_Quit();
	return (0);
}
