/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:55:15 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 19:43:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "priority_queue.h"
#include "lem-in.h"

static int	compare_cost(void *ptr1, void *ptr2)
{
	t_flow_node_data	*data1;
	t_flow_node_data	*data2;

	data1 = ((t_node*)ptr1)->data;
	data2 = ((t_node*)ptr2)->data;
	if (data1->path_cost > data2->path_cost)
		return (1);
	else if (data1->path_cost < data2->path_cost)
		return (-1);
	return (0);
}

#include "ft_printf.h"

static int	schedule_node(t_graph *flow_graph, t_pq *queue, t_list *edge,
				t_flow_node_data *this_data)
{
	size_t				next_id;
	t_flow_edge_data	*edge_data;
	t_flow_node_data	*next_data;
	t_node				*next_node;
	long				hypoth_cost;

	next_id = edge_head(flow_graph, LST_CONT(edge, size_t));
	next_data = node_flow_data(flow_graph, next_id);
	edge_data = edge_flow_data(flow_graph, LST_CONT(edge, size_t));
	hypoth_cost = this_data->path_cost + edge_data->weight
		+ this_data->potential - next_data->potential;
	if (!next_data->visited
		&& hypoth_cost < next_data->path_cost
		&& edge_data->flow < edge_data->capacity)
	{
		next_data->ancestor = LST_CONT(edge, size_t);
		next_data->path_cost = this_data->path_cost + edge_data->weight
			+ this_data->potential - next_data->potential;
		if (edge_data->weight + this_data->potential < next_data->potential)
			ft_dprintf(2, "edge %zu from %zu to %zu is rotten\n", LST_CONT(edge, size_t), edge_tail(flow_graph, LST_CONT(edge, size_t)), edge_head(flow_graph, LST_CONT(edge, size_t)));
		next_data->path_max_flow = ft_min(this_data->path_max_flow,
			edge_data->capacity - edge_data->flow);
		next_node = (t_node*)flow_graph->nodes.ptr + next_id;
		if (pq_add(queue, next_node, compare_cost) < 0)
			return (-1);
	}
	return (0);
}

static int	explore_neighbors(t_graph *flow_graph, t_pq *queue, t_node *node)
{
	t_flow_node_data	*this_data;
	t_list				*out_edges;

	this_data = node->data;
	this_data->visited = 1;
	out_edges = node->out_edges;
	while (out_edges)
	{
		if (schedule_node(flow_graph, queue, out_edges, this_data) < 0)
			return (-1);
		out_edges = out_edges->next;
	}
	return (0);
}

int			min_path(t_graph *flow_graph, size_t source)
{
	t_node	*pop;
	t_pq	queue;

	pq_init(&queue, sizeof(t_node));
	pq_add(&queue, &((t_node*)flow_graph->nodes.ptr)[source], compare_cost);
	while (!pq_empty(&queue))
	{
		pop = pq_pop(&queue, compare_cost);
		/*if (((t_flow_node_data*)pop->data)->flags & END)
			break ;*/
		explore_neighbors(flow_graph, &queue, pop);
		free(pop);
		pop = NULL;
	}
	pq_destroy(&queue);
	free(pop);
	return (0);
}
