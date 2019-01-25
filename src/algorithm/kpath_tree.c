/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:03:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/23 18:38:37 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "kpath.h"

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
	t_node	*path_node;
	size_t	edge_index;
	size_t	node_index;

	node_index = after_dev;
	while (((t_node*)snapshot->graph->nodes.ptr)[node_index].out_edges)
	{
		path_node = &((t_node*)snapshot->graph->nodes.ptr)[node_index];
		node_reserve(input, path_node);
		edge_index = *(size_t*)path_node->out_edges->content;
		node_index = ((t_edge*)snapshot->graph->edges.ptr)[edge_index].head;
	}
}
