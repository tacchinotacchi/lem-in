/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_graph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:04:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/13 14:46:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"

static int	create_flow_pair(t_graph *input,
				t_graph *flow_graph, size_t input_id)
{
	t_flow_node_data	node_data;
	t_flow_edge_data	edge_data;
	size_t				tail;
	size_t				head;

	node_data_init(&node_data);
	node_data.colony_id = input_id;
	add_node(flow_graph, &node_data, sizeof(t_flow_node_data));
	tail = flow_graph->nodes.length - 1;
	add_node(flow_graph, &node_data, sizeof(t_flow_node_data));
	head = flow_graph->nodes.length - 1;
	add_edge(flow_graph, tail, head, sizeof(edge_data));
	add_edge(flow_graph, head, tail, sizeof(edge_data));
	edge_data_init(&edge_data, 0, 0);
	edge_data.inverse = flow_graph->edges.length - 1;
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 2)) = edge_data;
	edge_data_init(&edge_data, 0, 1);
	edge_data.inverse = flow_graph->edges.length - 2;
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 1)) = edge_data;
	node_colony_data(input, input_id)->flow_in_id = tail;
	node_colony_data(input, input_id)->flow_out_id = head;
	return (0);
}

static int	add_special_node(t_graph *input,
				t_graph *flow_graph, size_t input_id)
{
	t_flow_node_data	node_data;
	size_t				new_id;

	node_data_init(&node_data);
	node_data.colony_id = input_id;
	if (node_colony_data(input, input_id)->flags & START)
		node_data.flags |= START;
	if (node_colony_data(input, input_id)->flags & END)
		node_data.flags |= END;
	add_node(flow_graph, &node_data, sizeof(node_data));
	new_id = flow_graph->nodes.length - 1;
	node_colony_data(input, input_id)->flow_in_id = new_id;
	node_colony_data(input, input_id)->flow_out_id = new_id;
	return (0);
}

static int	create_edge_pair(t_graph *input, t_graph *flow_graph,
				size_t input_id)
{
	size_t				colony_tail_id;
	size_t				colony_head_id;
	t_flow_edge_data	edge_data;

	colony_tail_id = edge_tail(input, input_id);
	colony_head_id = edge_head(input, input_id);
	add_edge(flow_graph,
		node_colony_data(input, colony_tail_id)->flow_out_id,
		node_colony_data(input, colony_head_id)->flow_in_id,
		sizeof(t_flow_edge_data));
	add_edge(flow_graph,
		node_colony_data(input, colony_head_id)->flow_in_id,
		node_colony_data(input, colony_tail_id)->flow_out_id,
		sizeof(t_flow_edge_data));
	edge_colony_data(input, input_id)->flow_id = flow_graph->edges.length - 2;
	edge_data_init(&edge_data, 1, 0);
	edge_data.capacity = 1;
	edge_data.colony_id = input_id;
	edge_data.inverse = flow_graph->edges.length - 1;
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 2)) = edge_data;
	edge_data_init(&edge_data, 1, 1);
	edge_data.colony_id = input_id;
	edge_data.inverse = flow_graph->edges.length - 2;
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 1)) = edge_data;
	return (0);
}

static int	create_edges(t_graph *input, t_graph *flow_graph)
{
	size_t	edge_id;
	size_t	tail_id;
	size_t	head_id;

	edge_id = 0;
	while (edge_id < input->edges.length)
	{
		tail_id = edge_tail(input, edge_id);
		head_id = edge_head(input, edge_id);
		if (!(node_colony_data(input, tail_id)->flags & END)
			&& !(node_colony_data(input, head_id)->flags & START))
			create_edge_pair(input, flow_graph, edge_id);
		edge_id++;
	}
	return (0);
}

int			transform_graph(t_graph *input, t_graph *flow_graph)
{
	size_t	node_id;

	array_init(&flow_graph->nodes, sizeof(t_node));
	array_init(&flow_graph->edges, sizeof(t_edge));
	node_id = 0;
	while (node_id < input->nodes.length)
	{
		if (node_colony_data(input, node_id)->flags & (START | END))
			add_special_node(input, flow_graph, node_id);
		else
			create_flow_pair(input, flow_graph, node_id);
		node_id++;
	}
	create_edges(input, flow_graph);
	return (0);
}
