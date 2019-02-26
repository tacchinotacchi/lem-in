/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_measure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:39:55 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/26 19:40:07 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "lem_in.h"

int		init_ants(t_graph *graph, size_t ants)
{
	size_t	node;

	node = 0;
	while (node < graph->nodes.length)
	{
		if (node_colony_data(graph, node)->flags & START)
			node_colony_data(graph, node)->ant = ants;
		else
			node_colony_data(graph, node)->ant = 0;
		node++;
	}
	return (0);
}

size_t	active_edge(t_graph *graph, size_t node_id)
{
	t_list	*in_edges;
	size_t	edge_id;
	size_t	active_edge;

	in_edges = *node_in_edges(graph, node_id);
	active_edge = graph->edges.length;
	while (in_edges)
	{
		edge_id = LST_CONT(in_edges, size_t);
		if (edge_colony_data(graph, edge_id)->in_use)
		{
			if (active_edge != graph->edges.length)
				return (graph->edges.length);
			active_edge = edge_id;
		}
		in_edges = in_edges->next;
	}
	return (active_edge);
}

size_t	walk_back(t_graph *graph, size_t node_id)
{
	t_colony_node_data	*node_data;
	size_t				edge_id;
	size_t				length;

	length = 0;
	node_data = node_colony_data(graph, node_id);
	while (!(node_data->flags & START))
	{
		edge_id = active_edge(graph, node_id);
		if (edge_id == graph->edges.length)
			return (graph->nodes.length);
		length++;
		node_id = edge_tail(graph, edge_id);
		node_data->ancestor = node_id;
		node_data = node_colony_data(graph, node_id);
	}
	return (length);
}

void	sort_paths(t_list **paths)
{
	t_list	*sorted;
	t_list	*traverse;
	t_list	*min;
	size_t	min_length;

	sorted = *paths;
	while (sorted && sorted->next)
	{
		traverse = sorted->next;
		min = sorted;
		min_length = LST_CONT(sorted, t_path).length;
		while (traverse)
		{
			if (LST_CONT(traverse, t_path).length < min_length)
			{
				min = traverse;
				min_length = LST_CONT(traverse, t_path).length;
			}
			traverse = traverse->next;
		}
		list_swap(sorted, min);
		sorted = sorted->next;
	}
}

t_list	*init_paths(t_lemin *info)
{
	t_list				*paths;
	t_list				*in_edges;
	t_path				new_path;
	t_colony_edge_data	*edge_data;

	new_path.ants = 0;
	new_path.running_ants = 0;
	paths = NULL;
	in_edges = *node_in_edges(&info->graph, info->end);
	while (in_edges)
	{
		edge_data = edge_colony_data(&info->graph, LST_CONT(in_edges, size_t));
		if (edge_data->in_use)
		{
			new_path.node = edge_tail(&info->graph,
				LST_CONT(in_edges, size_t));
			new_path.length = walk_back(&info->graph, new_path.node);
			list_add(&paths, list_new(&new_path, sizeof(t_path)));
		}
		in_edges = in_edges->next;
	}
	sort_paths(&paths);
	return (paths);
}
