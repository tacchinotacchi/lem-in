/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equilibrium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:49:23 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 02:52:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <math.h>

static void	node_attract(t_graph *graph, size_t tail, size_t head,
				t_visualizer *vis)
{
	float	distance;
	float	diff[3];
	float	desired;

	desired = vis->adj_matrix[tail * vis->width + head] ? 0.05f
		: 0.45f * pow(graph->nodes.length, 0.5);
	diff[0] = node_colony_data(graph, head)->coords[0]
		- node_colony_data(graph, tail)->coords[0];
	diff[1] = node_colony_data(graph, head)->coords[1]
		- node_colony_data(graph, tail)->coords[1];
	diff[2] = node_colony_data(graph, head)->coords[2]
		- node_colony_data(graph, tail)->coords[2];
	distance = sqrt(diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2]);
	node_colony_data(graph, tail)->accel[0] +=
		0.9f * 2.f * diff[0] * (distance - desired) / distance;
	node_colony_data(graph, tail)->accel[1] +=
		0.9f * 2.f * diff[1] * (distance - desired) / distance;
	node_colony_data(graph, tail)->accel[2] +=
		0.9f * 2.f * diff[2] * (distance - desired) / distance;
}

static void	update_coords(t_graph *graph, size_t id)
{
	node_colony_data(graph, id)->coords[0] +=
		node_colony_data(graph, id)->accel[0] / graph->nodes.length;
	node_colony_data(graph, id)->coords[1] +=
		node_colony_data(graph, id)->accel[1] / graph->nodes.length;
	node_colony_data(graph, id)->coords[2] +=
		node_colony_data(graph, id)->accel[2] / graph->nodes.length;
}

void		update_equilibrium(t_graph *graph, t_visualizer *vis)
{
	size_t	id;
	size_t	id_attract;

	id = 0;
	while (id < graph->nodes.length)
		ft_bzero(node_colony_data(graph, id++)->accel, sizeof(float) * 3);
	id = 0;
	while (id < graph->nodes.length)
	{
		id_attract = 0;
		while (id_attract < graph->nodes.length)
		{
			if (id != id_attract)
				node_attract(graph, id, id_attract, vis);
			id_attract++;
		}
		id++;
	}
	id = 0;
	while (id < graph->nodes.length)
	{
		update_coords(graph, id);
		id++;
	}
}
