/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:03:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 11:47:30 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "kpath.h"

/* TODO report conflicts to calling function */
void	node_reserve(t_lemin *input, t_node *path_node)
{
	t_node	*graph_node;

	graph_node = &((t_node*)input->graph.nodes.ptr)
		[((t_path_data*)path_node->data)->graph_id];
	((t_colony_data*)graph_node->data)->in_use_by = input->decision_depth;
}

t_list *walk_up_tree(t_lemin *input, t_path_graph *snapshot, t_path *path,
			size_t after_dev)
{
	t_list	*dev_node;
	t_node	*path_node;
	size_t	edge_index;
	size_t	node_index;
	int		nodes_left

	dev_node = NULL;
	node_index = after_dev;
	nodes_left = 1;
	while (nodes_left)
	{
		path_node = &((t_node*)snapshot->graph->nodes.ptr)[node_index];
		node_reserve(input, path_node);
		list_add(&path->nodes, list_new(&node_index, sizeof(size_t)));
		if (!dev_node && node_index != after_dev)
			dev_node = path->nodes;
		if (path_node->out_edges)
		{
			edge_index = *(size_t*)path_node->out_edges->content;
			node_index = ((t_edge*)snapshot->graph->edges.ptr)[edge_index].head;
		}
		else
			nodes_left = 0;
	}
	return (dev_node);
}
