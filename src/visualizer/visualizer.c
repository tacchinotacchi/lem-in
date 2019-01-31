/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:39:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 21:47:31 by aamadori         ###   ########.fr       */
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
		vis->window = SDL_CreateWindow("Lem-in visualizer",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 800,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (vis->window == NULL)
			return (-1);
		else if (acquire_context(vis, renderer) < 0)
			return (-1);
	}
	return (0);
}

void	free_resources(t_visualizer *v, t_renderer *renderer)
{
	SDL_DestroyWindow(v->window);
	v->window = NULL;
	SDL_Quit();
}

int		enter_reading_loop(t_lemin *input, t_visualizer *vis,
			t_renderer *renderer)
{
	int				quit;

	quit = 0;
	while (!quit)
	{
		while(SDL_PollEvent(&vis->event) != 0)
		{
			if (vis->event.type == SDL_QUIT)
				quit = 1;
			/* TODO handle events */
		}
		/*draw_graph(input, renderer);*/
		/* TODO decent fps limiter */
		SDL_Delay(6);
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
	parse_input(&input, L_ANTS | L_COMMENT);
	convert_input(&input, &renderer);
	if (init_sdl(&vis, &renderer) < 0)
	{
		ft_printf("Failed to acquire context: %s\n", SDL_GetError());
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
