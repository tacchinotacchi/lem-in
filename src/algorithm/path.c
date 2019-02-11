/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:55:15 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/11 13:03:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "priority_queue.h"
#include "lem_in.h"

static int	node_compare(const void *ptr1, const void *ptr2)
{
	const t_flow_node_data	*data1;
	const t_flow_node_data	*data2;

	data1 = ptr1;
	data2 = ptr2;
	if (data1->path_cost > data2->path_cost)
		return (-1);
	else if (data2->path_cost > data1->path_cost)
		return (1);
	return (0);
}

#include "ft_printf.h"

static void	explore_neighbor(t_graph *flow_graph, t_pq *queue,
				size_t node_id, size_t edge_id)
{
	t_flow_node_data	*node_data;
	t_flow_node_data	*next_data;
	t_flow_edge_data	*edge_data;
	long				new_cost;

	node_data = node_flow_data(flow_graph, node_id);
	edge_data = edge_flow_data(flow_graph, edge_id);
	next_data = node_flow_data(flow_graph,
		edge_head(flow_graph, edge_id));
	if (edge_data->flow < edge_data->capacity && !next_data->visited)
	{
		new_cost = node_data->path_cost + edge_data->weight
			+ node_data->potential - next_data->potential;
		if (new_cost < next_data->path_cost)
		{
			next_data->path_cost = new_cost;
			next_data->ancestor = edge_id;
			next_data->path_length = node_data->path_cost + 1;
			next_data->path_max_flow = ft_min(node_data->path_max_flow,
				edge_data->capacity - edge_data->flow);
			pq_add(queue, next_data, node_compare);
		}
	}
}

static void	explore_node(t_graph *flow_graph, t_pq *queue, size_t node_id)
{
	t_flow_node_data	*node_data;
	t_flow_node_data	*prev_data;
	t_list				*out_edges;

	node_data = node_flow_data(flow_graph, node_id);
	if (node_data->visited)
		return ;
	node_data->visited = 1;
	if (node_data->flags & START)
		node_data->next_potential = 0;
	else
	{
		prev_data = node_flow_data(flow_graph,
			edge_tail(flow_graph, node_data->ancestor));
		node_data->next_potential = prev_data->next_potential
			+ edge_flow_data(flow_graph, node_data->ancestor)->weight;
	}
	out_edges = *node_out_edges(flow_graph, node_id);
	while (out_edges)
	{
		explore_neighbor(flow_graph, queue, node_id, LST_CONT(out_edges, size_t));
		out_edges = out_edges->next;
	}
}

int		min_path(t_graph *flow_graph, size_t source)
{
	t_pq				queue;
	t_flow_node_data	*pop;

	pq_init(&queue, sizeof(t_flow_node_data));
	pq_add(&queue, node_flow_data(flow_graph, source), node_compare);
	while (!pq_empty(&queue))
	{
		pop = pq_pop(&queue, node_compare);
		explore_node(flow_graph, &queue, pop->own_id);
		if (pop->flags & END)
			break ;
		free(pop);
		pop = NULL;
	}
	free(pop);
	pq_destroy(&queue);
	return (0);
}
