/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:06:06 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/13 14:17:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "lem_in.h"

void		reset_node_data(t_graph *flow_graph)
{
	t_flow_node_data	*data;
	size_t				index;

	index = 0;
	while (index < flow_graph->nodes.length)
	{
		data = node_flow_data(flow_graph, index);
		data->ancestor = 0;
		data->path_max_flow = INT_MAX;
		data->path_length = 0;
		if (data->flags & START)
			data->path_cost = 0;
		else
			data->path_cost = INT_MAX;
		index++;
	}
}

void		use_augmenting(t_graph *flow_graph, size_t source, int max_flow)
{
	t_flow_node_data	*node_data;
	t_flow_edge_data	*edge_data;
	size_t				node_id;
	size_t				edge_id;

	node_id = source;
	node_data = node_flow_data(flow_graph, node_id);
	while (!(node_data->flags & START))
	{
		edge_id = node_data->ancestor;
		edge_data = edge_flow_data(flow_graph, edge_id);
		edge_data->flow += max_flow;
		edge_flow_data(flow_graph,
			edge_data->inverse)->flow -= max_flow;
		node_id = edge_tail(flow_graph, edge_id);
		node_data = node_flow_data(flow_graph, node_id);
	}
}

int			increase_flow(t_graph *flow_graph, size_t source, size_t sink)
{
	char		found;

	found = 1;
	reset_node_data(flow_graph);
	if (min_path(flow_graph, source) < 0)
		return (-1);
	if (node_flow_data(flow_graph, sink)->path_cost == INT_MAX)
		found = 0;
	else
		use_augmenting(flow_graph, sink, 1);
	return (found);
}
