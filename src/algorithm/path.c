/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:55:15 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/05 20:21:19 by aamadori         ###   ########.fr       */
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

static int	explore_neighbors(t_graph *flow_graph, t_pq *queue, t_node *node)
{
	t_flow_node_data	*this_data;
	t_flow_node_data	*next_data;
	size_t				next_id;
	t_flow_edge_data	*edge_data;
	t_list				*out_edges;

	this_data = node->data;
	out_edges = node->out_edges;
	while (out_edges)
	{
		next_id = edge_head(flow_graph, LST_CONT(out_edges, size_t));
		next_data = node_flow_data(flow_graph, next_id);
		edge_data = edge_flow_data(flow_graph, LST_CONT(out_edges, size_t));
		if (next_data->path_cost == INT_MAX
			&& edge_data->flow < edge_data->capacity)
		{
			next_data->ancestor = LST_CONT(out_edges, size_t);
			next_data->path_cost = this_data->path_cost + edge_data->weight
				+ this_data->potential - next_data->potential;
			/* TODO path length probably useless now */
			next_data->path_length = this_data->path_length + 1;
			next_data->path_max_flow = ft_min(this_data->path_max_flow,
				edge_data->capacity - edge_data->flow);
			pq_add(queue, &((t_node*)flow_graph->nodes.ptr)[next_id], compare_cost);
		}
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
		if (((t_flow_node_data*)pop->data)->flags & END)
			break;
		explore_neighbors(flow_graph, &queue, pop);
		free(pop);
		pop = NULL;
	}
	pq_destroy(&queue);
	free(pop);
	return (0);
}
