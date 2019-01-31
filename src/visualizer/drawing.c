/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 21:50:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "visualizer.h"
#include <SDL.h>

static float	transform_x(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_x_coord);
	result /= (float)(info->max_x_coord - info->min_x_coord);
	return (result);
}

static float	transform_y(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_y_coord);
	result /= (float)(info->max_y_coord - info->min_y_coord);
	return (result);
}

void	convert_input(t_lemin *info, t_renderer *renderer)
{
	size_t	id;

	id = 0;
	array_init(&renderer->node_info, sizeof(float[3]));
	while (id < info->graph.nodes.length)
	{
		array_push_back(&renderer->node_info, (float[3]){
			transform_x(info, node_colony_data(&info->graph, id)->x),
			transform_y(info, node_colony_data(&info->graph, id)->y),
			0.0f
		});
		id++;
	}
	id = 0;
	array_init(&renderer->edge_info, sizeof(int[2]));
	while (id < info->graph.edges.length)
	{
		array_push_back(&renderer->edge_info, (int[2]){
			edge_tail(&info->graph, id),
			edge_head(&info->graph, id)
		});
		id++;
	}
}

int		draw_graph()
{
	return (0);
}
