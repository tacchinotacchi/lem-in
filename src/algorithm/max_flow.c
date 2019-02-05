/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:06:06 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/05 05:09:29 by aamadori         ###   ########.fr       */
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
		data->path_max_flow = INT_MAX;
		if (data->flags & START)
			data->path_cost = 0;
		else
			data->path_cost = INT_MAX;
		index++;
	}
}

static void	reduce_weights(t_graph *flow_graph, size_t node_id)
{
	t_flow_edge_data	*edge_data;
	t_flow_node_data	*this_data;
	t_flow_node_data	*next_data;
	t_list				*traverse;

	this_data = node_flow_data(flow_graph, node_id);
	traverse = *node_out_edges(flow_graph, node_id);
	while (traverse)
	{
		edge_data = edge_flow_data(flow_graph, LST_CONT(traverse, size_t));
		next_data = node_flow_data(flow_graph,
			edge_head(flow_graph, LST_CONT(traverse, size_t)));
		edge_data->weight += this_data->path_cost - next_data->path_cost;
		traverse = traverse->next;
	}
	traverse = *node_in_edges(flow_graph, node_id);
	while (traverse)
	{
		edge_data = edge_flow_data(flow_graph, LST_CONT(traverse, size_t));
		next_data = node_flow_data(flow_graph,
			edge_tail(flow_graph, LST_CONT(traverse, size_t)));
		edge_data->weight += next_data->path_cost - this_data->path_cost;
		traverse = traverse->next;
	}
}

void	use_augmenting(t_graph *flow_graph, size_t source, int max_flow)
{
	t_flow_node_data	*node_data;
	t_flow_edge_data	*edge_data;
	size_t				node_id;
	size_t				edge_id;

	node_id = source;
	reduce_weights(flow_graph, node_id);
	node_data = node_flow_data(flow_graph, node_id);
	while (!(node_data->flags & START))
	{
		edge_id = node_data->ancestor;
		edge_data = edge_flow_data(flow_graph, edge_id);
		edge_data->flow += max_flow;
		edge_flow_data(flow_graph,
			edge_data->inverse)->flow -= max_flow;
		node_id = edge_tail(flow_graph, edge_id);
		reduce_weights(flow_graph, node_id);
		node_data = node_flow_data(flow_graph, node_id);
	}
}

int		min_cost_flow(t_graph *flow_graph, size_t source, size_t sink, int flow)
{
	int			max_flow;
	char		found;

	(void)flow;
	found = 1;
	while (found)
	{
		reset_node_data(flow_graph);
		min_path(flow_graph, source);
		if (node_flow_data(flow_graph, sink)->path_cost == INT_MAX)
			found = 0;
		else
		{
			max_flow = node_flow_data(flow_graph, sink)->path_max_flow;
			use_augmenting(flow_graph, sink, max_flow);
		}
	}
	return (0);
}
