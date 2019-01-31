/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:22:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/28 00:00:17 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H

#include "adjacency_list.h"
#include "lem-in.h"
#include <SDL.h>

typedef struct	s_textures
{
	SDL_Renderer *renderer;
	SDL_Texture	*node;
	SDL_Texture *start;
	SDL_Texture *end;
	SDL_Texture	*digits[10];
}				t_textures;

typedef struct	s_visualizer
{
	SDL_Window	*window;
	SDL_Surface	*surf;
	SDL_Event	event;
	int			loop;
}				t_visualizer;

int		init_textures(t_textures *textures);
int		init_sdl(t_visualizer *v, t_textures *textures);
void	ft_close(t_visualizer *v, t_textures *textures);
void 	draw_graph(t_lemin *input, t_textures *textures);

#endif
