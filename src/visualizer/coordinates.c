/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 01:42:17 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/05 02:49:15 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static float	transform_x(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_x_coord);
	result *= 1.8f/(float)(info->max_x_coord - info->min_x_coord);
	result = result - 1.8f/2.f;
	return (result);
}

static float	transform_y(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_y_coord);
	result *= 1.8f/(float)(info->max_y_coord - info->min_y_coord);
	result = result - 1.8f/2.f;
	return (result);
}

void	generate_coords(t_lemin *info, t_visualizer *vis)
{
	size_t	id;

	vis->width = info->graph.nodes.length;
	vis->adj_matrix = ft_memalloc(vis->width * vis->width);
	id = 0;
	while (id < info->graph.nodes.length)
	{
		node_colony_data(&info->graph, id)->coords[0] = transform_x(info,
			node_colony_data(&info->graph, id)->x);
		node_colony_data(&info->graph, id)->coords[1] = transform_y(info,
			node_colony_data(&info->graph, id)->y);
		node_colony_data(&info->graph, id)->coords[2] = 1.f * sin(
			node_colony_data(&info->graph, id)->x);
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

void	convert_input(t_lemin *info, t_renderer *renderer)
{
	size_t	id;

	id = 0;
	renderer->node_coords.length = 0;
	while (id < info->graph.nodes.length)
	{
		array_push_back(&renderer->node_coords,
			node_colony_data(&info->graph, id)->coords);
		id++;
	}
	id = 0;
	renderer->edge_indices.length = 0;
	while (id < info->graph.edges.length)
	{
		array_push_back(&renderer->edge_indices, (GLuint[2]){
			edge_tail(&info->graph, id),
			edge_head(&info->graph, id)
		});
		id += 2;
	}
}

void	update_ants(t_visualizer *vis, t_renderer *renderer)
{
	/* TODO */
}

/* TODO remove ants absorbed by end */

int		compare_ant(const void *ptr1, const void *ptr2)
{
	size_t	id1;
	size_t	id2;

	id1 = *(size_t*)ptr1;
	id2 = *(size_t*)ptr2;
	if (id1 > id2)
		return (1);
	else if (id1 < id2)
		return (-1);
	return (0);
}

void	process_instructions(t_visualizer *vis, t_list *instructions)
{
	t_list			*traverse;
	t_tree			*node;
	t_ant_data		data;
	t_instruction	instr;

	traverse = instructions;
	while (traverse)
	{
		instr = LST_CONT(traverse, t_instruction);
		if (instr.flusher)
			break;
		data.ant_id = instr.ant_id;
		node = tree_search(vis->ant_positions, &data, compare_ant);
		if (!node)
		{
			data.target_node = instr.node_id;
			node = node_create(&data, sizeof(t_ant_data));
			tree_insert(&vis->ant_positions, node, compare_ant);
		}
		else
			LST_CONT(node, t_ant_data).target_node = instr.node_id;
		traverse = traverse->next;
	}
}
