/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:03:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 15:59:00 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "kpath.h"

size_t	add_node_pseudotree(t_path_graph *snapshot, size_t parent, size_t graph_id)
{
	t_path_data new_data;
	size_t		new_index;

	new_data.conflicts = NULL;
	new_data.creation_time = snapshot->time_frame;
	new_data.graph_id = graph_id;
	add_node(snapshot->graph, &new_data, sizeof(t_path_data));
	new_index = snapshot->graph->nodes.length - 1;
	(node_path_data(snapshot->graph, new_index))->pseudotree_id = new_index;
	return (new_index);
}

size_t	add_node_snapshot(t_path_graph *snapshot, size_t parent, size_t graph_id)
{
	t_list		*traverse;
	t_path_data	*found;
	size_t		tail;

	found = NULL;
	traverse = node_in_edges(snapshot->graph, parent);
	while (traverse)
	{
		tail = edge_tail(snapshot->graph, *(size_t*)traverse->content);
		if ((node_path_data(snapshot->graph, tail))->graph_id == graph_id)
		{
			found = ((t_node*)snapshot->graph->nodes.ptr)[tail].data;
			break;
		}
		traverse = traverse->next;
	}
	if (found)
		found->creation_time = ft_min(found->creation_time, snapshot->time_frame);
	else
		tail = add_node_pseudotree(snapshot, parent, graph_id);
	return (tail);
}

void	node_reserve(t_lemin *input, t_path_data *path_data)
{
	t_node	*graph_node;

	graph_node = &((t_node*)input->graph.nodes.ptr)[path_data->graph_id];
	((t_colony_data*)graph_node->data)->marked_decision = input->decision_depth;
	((t_colony_data*)graph_node->data)->marked_path_id = path_data->pseudotree_id;
}

size_t	walk_up_tree(t_lemin *input, t_path_graph *snapshot, t_path *path,
			size_t after_dev)
{
	t_node	*path_node;
	size_t	edge_index;
	size_t	node_index;
	size_t	dev_node;
	int		nodes_left;

	node_index = after_dev;
	nodes_left = 1;
	while (nodes_left)
	{
		path_node = &((t_node*)snapshot->graph->nodes.ptr)[node_index];
		list_add(&path->nodes, list_new(&node_index, sizeof(size_t)));
		if (path_node->out_edges)
		{
			edge_index = *(size_t*)path_node->out_edges->content;
			if (node_index == after_dev)
				dev_node = edge_head(snapshot->graph, edge_index);
			node_index = edge_head(snapshot->graph, edge_index);
		}
		else
			nodes_left = 0;
	}
	return (dev_node);
}

void	prune_path(t_lemin *input, t_path_graph *snapshot, t_path *path,
			size_t after_dev)
{
	size_t	curr_graph_node;
	size_t	curr_path_node;
	size_t	cost;

	curr_path_node = after_dev;
	curr_graph_node = (node_path_data(snapshot->graph, after_dev))->graph_id;
	cost = (node_path_data(snapshot->graph, after_dev))->cost;
	/* TODO set GOAL flag */
	while (!((node_colony_data(&input->graph, curr_graph_node))->flags & GOAL))
	{
		curr_graph_node = *(size_t*)(node_out_edges(&input->graph, curr_graph_node))->content;
		curr_path_node = add_node_snapshot(snapshot, curr_path_node, curr_graph_node);
		list_append(&path->nodes, list_new(&curr_path_node, sizeof(size_t)));
		(node_path_data(snapshot->graph, curr_path_node))->cost = ++cost;
	}
	curr_path_node = add_node_snapshot(snapshot, curr_path_node, curr_graph_node);
	(node_path_data(snapshot->graph, curr_path_node))->cost = ++cost;
	list_append(&path->nodes, list_new(&curr_path_node, sizeof(size_t)));
}
