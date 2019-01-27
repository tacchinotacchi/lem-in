/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/27 23:45:53 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "adjacency_list.h"
#include "visualizer.h"
#include "parser.h"
#include "lem-in.h"
#include <SDL.h>

int		init_sdl(t_visualizer *v, t_textures *textures)
{
	int	success;

	success = 1;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize %s\n", SDL_GetError());
		success = 0;
	}
	else
	{
		v->window = SDL_CreateWindow("Lem-in visualizer", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
		if (v->window == NULL)
		{
			printf("window could not be created %s\n", SDL_GetError());
			success = 0;
		}
		else
			textures->renderer = SDL_CreateRenderer(v->window, -1, SDL_RENDERER_ACCELERATED);
		if (!textures->renderer || init_textures(textures) < 0)
			success = 0;
	}
	return (success);
}

void	ft_close(t_visualizer *v, t_textures *textures)
{
	SDL_DestroyRenderer(textures->renderer);
	SDL_DestroyWindow(v->window);
	v->window = NULL;
	SDL_Quit();
}

int		enter_reading_loop(t_lemin *input, t_visualizer *v, t_textures *textures)
{
	int				quit;

	quit = 0;
	while (!quit)
	{
		while(SDL_PollEvent(&v->event) != 0)
		{
			if (v->event.type == SDL_QUIT)
				quit = 1;
		}
		draw_graph(input, textures);
		SDL_Delay(1000);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_lemin 		input;
	t_visualizer	v;
	t_textures		textures;

	(void)argc;
	(void)argv;
	ft_bzero(&input, sizeof(t_lemin));
	parse_input(&input, L_ANTS | L_COMMENT);
	if (!init_sdl(&v, &textures))
	{
		printf("failed to initialize!\n");
		return (0);
	}
	else
		enter_reading_loop(&input, &v, &textures);
	ft_close(&v, &textures);
	/*free_all(input); free_all lem-in inputs*/
	return (0);
}
