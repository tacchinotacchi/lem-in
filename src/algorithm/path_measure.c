/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_measure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 11:39:55 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/12 12:09:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"
#include "lem-in.h"

int		init_ants(t_lemin *info)
{
	size_t	node;

	node = 0;
	while (node < info->graph.nodes.length)
	{
		node_colony_data(&info->graph, node)->ant = 0;
		node++;
	}
	node_colony_data(&info->graph, info->start)->ant = info->ants;
	return (0);
}

size_t	walk_back(t_graph *graph)
{
	t_colony_node_data	*node_data;
	t_list				*in_edges;
    size_t              node_id;
	size_t				edge_id;
	size_t				length;

	length = 0;
	node_data = node_colony_data(graph, node_id);
	while (!(node_data->flags & START))
	{
        list_add(&node_list, &node_id);
		in_edges = *node_in_edges(graph, index);
		edge_id = graph->edges.length;
		while (in_edges)
		{
			edge_id = LST_CONT(in_edges, size_t);
			/* TODO CHECK THIS HAPPENS EXACTLY ONCE!!! */
			if (edge_colony_data(graph, edge_id)->in_use)
				break ;
			in_edges = in_edges->next;
		}
		if (edge_id == graph->edges.length)
			return (graph->nodes.length);
		length++
		node_id = edge_tail(graph, edge_id);
        node_data->ancestor = node_id;
		node_data = node_colony_data(graph, node_id);
	}
    list_add(&node_list, &node_id);
	return (length);
}

void	sort_paths(t_list **paths)
{
	t_list	*sorted;
	t_list	*traverse;
	t_list	*min;
	size_t	min_length;

	sorted = *paths;
	while (sorted->next)
	{
		traverse = sorted->next;
		min = sorted;
		while (traverse)
		{
			if (LST_CONT(traverse, t_path).length
				< LST_CONT(min, t_path).length)
				min = traverse;
			traverse = traverse->next;
		}
		list_swap(sorted, min);
		sorted = sorted->next;
	}
	*paths = sorted;
}

t_list	*init_paths(t_lemin *info)
{
	t_list				*paths;
	t_list				*in_edges;
	t_path				new_path;
	t_colony_edge_data	*edge_data;

	new_path.ants = 0;
    new_path.running_ants = 0;
	in_edges = *node_in_edges(&info->graph, info->ants);
	while (in_edges)
	{
		edge_data = edge_colony_data(&info->graph, LST_CONT(in_edges, size_t));
		if (edge_data->in_use)
		{
			new_path.node = edge_tail(&info->graph,
				LST_CONT(in_edges, size_t));
			new_path.length = walk_back(&info->graph);
			list_add(&paths, list_new(&new_path, sizeof(t_path)));
		}
		in_edges = in_edges->next;
	}
	sort_paths(&paths);
	return (paths);
}