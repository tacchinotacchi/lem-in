/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:36:49 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/11 19:15:13 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static float	transform_x(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_x_coord);
	result *= 1.8f / (float)(info->max_x_coord - info->min_x_coord);
	result = result - 1.8f / 2.f;
	return (result);
}

static float	transform_y(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_y_coord);
	result *= 1.8f / (float)(info->max_y_coord - info->min_y_coord);
	result = result - 1.8f / 2.f;
	return (result);
}

void			generate_coords(t_lemin *info, t_visualizer *vis)
{
	size_t	id;

	vis->width = info->graph.nodes.length;
	vis->adj_matrix = ft_memalloc(vis->width * vis->width);
	id = 0;
	while (id < info->graph.nodes.length)
	{
		node_colony_data(&info->graph, id)->coords[0] = transform_x(info,
			node_colony_data(&info->graph, id)->x)
			+ 0.2f * (float)(rand() % 101) / 100.f - 0.1f;
		node_colony_data(&info->graph, id)->coords[1] = transform_y(info,
			node_colony_data(&info->graph, id)->y)
			+ 0.2f * (float)(rand() % 101) / 100.f - 0.1f;
		node_colony_data(&info->graph, id)->coords[2] =
		20.f * (float)(rand() % 101) / 100.f - 10.f;
		id++;
	}
	id = 0;
	while (id < info->graph.edges.length)
	{
		vis->adj_matrix[vis->width * edge_tail(&info->graph, id)
			+ edge_head(&info->graph, id)] = 1;
		id++;
	}
}

void			convert_input(t_lemin *info, t_renderer *renderer)
{
	size_t	id;

	id = 0;
	array_clear(&renderer->node_coords, NULL);
	while (id < info->graph.nodes.length)
	{
		array_push_back(&renderer->node_coords,
			node_colony_data(&info->graph, id)->coords);
		id++;
	}
	id = 0;
	array_clear(&renderer->edge_indices, NULL);
	while (id < info->graph.edges.length)
	{
		array_push_back(&renderer->edge_indices, (const GLuint[2]){
			edge_tail(&info->graph, id),
			edge_head(&info->graph, id)
		});
		id += 2;
	}
}
