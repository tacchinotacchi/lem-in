/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:06:06 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 19:47:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "lem-in.h"

void		reset_node_data(t_graph *flow_graph)
{
	t_flow_node_data	*data;
	size_t				index;

	index = 0;
	while (index < flow_graph->nodes.length)
	{
		data = node_flow_data(flow_graph, index);
		data->ancestor = 0;
		data->visited = 0;
		data->path_max_flow = INT_MAX;
		if (data->flags & START)
			data->path_cost = 0;
		else
			data->path_cost = INT_MAX;
		index++;
	}
}

static void	reduce_weights(t_graph *flow_graph)
{
		t_flow_node_data	*node_data;
		size_t				node_id;

		node_id = 0;
		while (node_id < flow_graph->nodes.length)
		{
			node_data = node_flow_data(flow_graph, node_id);
			if (node_data->visited)
				node_data->potential += node_data->path_cost;
			node_id++;
		}
}

#include "ft_printf.h"

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
		char possible;
		edge_data = edge_flow_data(flow_graph, edge_id);
		edge_data->flow += max_flow;
		possible = edge_flow_data(flow_graph, edge_data->inverse)->flow <  edge_flow_data(flow_graph, edge_data->inverse)->capacity;
		edge_flow_data(flow_graph,
			edge_data->inverse)->flow -= max_flow;
		if (!possible && edge_flow_data(flow_graph, edge_data->inverse)->flow <  edge_flow_data(flow_graph, edge_data->inverse)->capacity)
			ft_dprintf(2, "opened up path %zu from %zu to %zu\n", edge_data->inverse, node_id, edge_tail(flow_graph, edge_id));
		node_id = edge_tail(flow_graph, edge_id);
		node_data = node_flow_data(flow_graph, node_id);
	}
}

int			min_cost_flow(t_graph *flow_graph, size_t source,
				size_t sink, int allowed_flow)
{
	int			flow;
	int			max_flow;
	char		found;

	flow = 0;
	found = 1;
	while (found && flow < allowed_flow)
	{
		reset_node_data(flow_graph);
		if (min_path(flow_graph, source) < 0)
			return (-1);
		if (node_flow_data(flow_graph, sink)->path_cost == INT_MAX)
			found = 0;
		else
		{
			max_flow = node_flow_data(flow_graph, sink)->path_max_flow;
			max_flow = ft_min(flow + max_flow, allowed_flow) - flow;
			flow += max_flow;
			reduce_weights(flow_graph);
			use_augmenting(flow_graph, sink, max_flow);
		}
	}
	return (0);
}
