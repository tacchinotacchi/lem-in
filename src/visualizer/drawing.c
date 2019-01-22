/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 22:10:20 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "visualizer.h"

static int	transform_x(t_lemin *input, int coord)
{
	float	result;

	result = (float)(coord - input->min_x_coord);
	result /= (float)(input->max_x_coord - input->min_x_coord);
	result = result * 500.f + 50.f;
	return (result);
}

static int	transform_y(t_lemin *input, int coord)
{
	float	result;

	result = (float)(coord - input->min_y_coord);
	result /= (float)(input->max_y_coord - input->min_y_coord);
	result = result * 500.f + 50.f;
	return (result);
}

static void handle_flags(int x, int y, int flags, t_textures *textures)
{
	SDL_Rect	dest;

	dest.w = 30;
	dest.h = 70;
	dest.x = x - 20;
	dest.y = y;
	if (flags & START)
		SDL_RenderCopy(textures->renderer, textures->start, NULL, &dest);
	else if (flags & END)
		SDL_RenderCopy(textures->renderer, textures->start, NULL, &dest);
}

static void draw_nodes(t_lemin *input, t_textures *textures)
{
	SDL_Rect	dest;
	size_t		index;

	index = 0;
	dest.w = 30;
	dest.h = 30;
	while (index < input->graph.nodes.length)
	{
		dest.x = transform_x(input, ((t_colony_data*)
			((t_node*)input->graph.nodes.ptr)[index].data)->x) - 15;
		dest.y = transform_y(input, ((t_colony_data*)
			((t_node*)input->graph.nodes.ptr)[index].data)->y) - 15;
		handle_flags(dest.x, dest.y, ((t_colony_data*)
			((t_node*)input->graph.nodes.ptr)[index].data)->flags, textures);
		SDL_RenderCopy(textures->renderer, textures->node, NULL, &dest);
		index++;
	}
}

static void draw_edges(t_lemin *input, t_textures *textures)
{
	size_t	index;
	t_colony_data	*head;
	t_colony_data	*tail;

	index = 0;
	while (index < input->graph.edges.length)
	{
		head = ((t_node*)input->graph.nodes.ptr)
			[((t_edge*)input->graph.edges.ptr)[index].head].data;
		tail = ((t_node*)input->graph.nodes.ptr)
			[((t_edge*)input->graph.edges.ptr)[index].tail].data;
		SDL_RenderDrawLine(textures->renderer,
			head->x, head->y, tail->x, tail->y);
		index++;
	}
}

void draw_graph(t_lemin *input, t_textures *textures)
{
	SDL_SetRenderDrawColor(textures->renderer, 255, 255, 255, 255);
	SDL_RenderClear(textures->renderer);
	draw_nodes(input, textures);
	draw_edges(input, textures);
	SDL_RenderPresent(textures->renderer);
}
