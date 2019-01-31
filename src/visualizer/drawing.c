/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/31 22:36:14 by aamadori         ###   ########.fr       */
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
	array_init(&renderer->node_coords, sizeof(float[3]));
	while (id < info->graph.nodes.length)
	{
		array_push_back(&renderer->node_coords, (float[3]){
			transform_x(info, node_colony_data(&info->graph, id)->x),
			transform_y(info, node_colony_data(&info->graph, id)->y),
			0.0f
		});
		id++;
	}
	id = 0;
	array_init(&renderer->edge_vao, sizeof(int[2]));
	while (id < info->graph.edges.length)
	{
		array_push_back(&renderer->edge_vao, (int[2]){
			edge_tail(&info->graph, id),
			edge_head(&info->graph, id)
		});
		id++;
	}
}

void	draw_graph(t_renderer *renderer)
{
	glUseProgram(renderer->node_program);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->node_buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0,
		renderer->node_coords.length * sizeof(float[3]),
		renderer->node_coords.ptr);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, 0, renderer->node_coords.length);
}
