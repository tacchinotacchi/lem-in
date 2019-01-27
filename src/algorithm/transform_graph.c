/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_graph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:04:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/27 23:34:50 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "algorithm.h"

static int	create_flow_pair(t_graph *input,
				t_graph *flow_graph, size_t input_id)
{
	t_flow_node_data	node_data;
	t_flow_edge_data	edge_data;
	size_t				tail;
	size_t				head;

	node_data.colony_id = input_id;
	add_node(flow_graph, &node_data, sizeof(t_flow_node_data));
	head = flow_graph->nodes.length - 1;
	add_node(flow_graph, &node_data, sizeof(t_flow_node_data));
	tail = flow_graph->nodes.length - 1;
	add_edge(flow_graph, tail, head, sizeof(edge_data));
	edge_data.capacity = 1;
	edge_data.flow = 0;
	edge_data.weight = 0;
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 1)) = edge_data;
	node_colony_data(input, input_id)->flow_in_id = tail;
	node_colony_data(input, input_id)->flow_out_id = head;
	return (0);
}

static int	set_edges(t_graph *input, t_graph *flow_graph, size_t input_id)
{
	size_t				colony_tail_id;
	size_t				colony_head_id;
	t_flow_edge_data	edge_data;

	edge_data.capacity = 1;
	edge_data.flow = 0;
	edge_data.weight = 1;
	colony_tail_id = edge_tail(input, input_id);
	colony_head_id = edge_head(input, input_id);
	add_edge(flow_graph,
		node_colony_data(input, colony_tail_id)->flow_out_id,
		node_colony_data(input, colony_head_id)->flow_in_id,
		sizeof(t_flow_edge_data));
	*(edge_flow_data(flow_graph, flow_graph->edges.length - 1)) = edge_data;
	return (0);
}

int		transform_graph(t_graph *input, t_graph *flow_graph)
{
	size_t	input_id;

	input_id = 0;
	while (input_id < input->nodes.length)
		create_flow_pair(input, flow_graph, input_id++);
	input_id = 0;
	while (input_id < input->edges.length)
		set_edges(input, flow_graph, input_id);
	return (0);
}
