/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:06:06 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/29 13:43:47 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "lem-in.h"

void	reset_node_data(t_graph *flow_graph)
{
	t_flow_node_data	*data;
	size_t				index;

	index = 0;
	while (index < flow_graph->nodes.length)
	{
		data = node_flow_data(flow_graph, index);
		data->ancestor = 0;
		data->path_length = 0;
		if (data->flags & START)
			data->path_cost = 0;
		else
			data->path_cost = INT_MAX;
		index++;
	}
}

t_aug_path	walk_back_path(t_graph *flow_graph, size_t sink)
{
	t_flow_edge_data	*edge_data;
	t_aug_path	augmenting;
	size_t		node_id;
	size_t		edge_id;

	if (node_flow_data(flow_graph, sink)->path_cost == INT_MAX)
		return ((t_aug_path){NULL, 0});
	augmenting.path = NULL;
	node_id = sink;
	augmenting.max_flow = INT_MAX;
	while (!(node_flow_data(flow_graph, node_id)->flags & START))
	{

		edge_id = node_flow_data(flow_graph, node_id)->ancestor;
		list_add(&augmenting.path, list_new(&edge_id, sizeof(size_t)));
		edge_data = edge_flow_data(flow_graph, edge_id);
		augmenting.max_flow = ft_min(augmenting.max_flow,
			edge_data->capacity - edge_data->flow);
		node_id = edge_tail(flow_graph, edge_id);
	}
	return (augmenting);
}

void	use_augmenting(t_graph *flow_graph, t_aug_path augmenting)
{
	t_list	*traverse;
	size_t	inverse;

	traverse = augmenting.path;
	while (traverse)
	{
		edge_flow_data(flow_graph, LST_CONT(traverse, size_t))->flow += augmenting.max_flow;
		inverse = edge_flow_data(flow_graph, LST_CONT(traverse, size_t))->inverse;
		edge_flow_data(flow_graph, inverse)->flow -= augmenting.max_flow;
		traverse = traverse->next;
	}
}

int		min_cost_flow(t_graph *flow_graph, size_t source, size_t sink, int flow)
{
	t_aug_path	augmenting;
	char		found;

	(void)flow;
	found = 1;
	augmenting = (t_aug_path){NULL, 0};
	while (found)
	{
		list_del(&augmenting.path, free_stub);
		reset_node_data(flow_graph);
		min_path(flow_graph, source);
		if (node_flow_data(flow_graph, sink)->path_cost == INT_MAX)
			found = 0;
		else
		{
			augmenting = walk_back_path(flow_graph, sink);
			use_augmenting(flow_graph, augmenting);
		}
	}
	list_del(&augmenting.path, free_stub);
	return (0);
}
