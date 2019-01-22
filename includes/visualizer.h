/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:22:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 21:27:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VISUALIZER_H
# define _VISUALIZER_H

#include "adjacency_list.h"
#include "lem-in.h"
#include "SDL.h"

typedef struct	s_textures
{
	SDL_Renderer *renderer;
	SDL_Texture	*node;
	SDL_Texture *start;
	SDL_Texture *end;
	SDL_Texture	*digits[10];
}				t_textures;

int		init_textures(t_textures *textures);
void 	draw_graph(t_lemin *input, t_textures *textures);

#endif
