/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:55:15 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 14:47:42 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "queue.h"
#include "lem_in.h"

static int	try_relaxation(t_graph *flow_graph, size_t node_id, size_t edge_id)
{
	t_flow_node_data	*node_data;
	t_flow_node_data	*next_data;
	t_flow_edge_data	*edge_data;
	size_t				next_id;
	long				new_cost;

	edge_data = edge_flow_data(flow_graph, edge_id);
	next_id = edge_head(flow_graph, edge_id);
	next_data = node_flow_data(flow_graph, next_id);
	node_data = node_flow_data(flow_graph, node_id);
	new_cost = node_data->path_cost + edge_data->weight;
	if (edge_data->flow < edge_data->capacity
		&& new_cost < next_data->path_cost)
	{
		next_data->ancestor = edge_id;
		next_data->path_cost = new_cost;
		next_data->path_max_flow = ft_min(node_data->path_max_flow,
			edge_data->capacity - edge_data->flow);
		next_data->path_length = node_data->path_length + 1;
		return (1);
	}
	return (0);
}

static void	explore_neighbors(t_graph *flow_graph, t_queue *queue,
				char *in_queue, size_t node_id)
{
	size_t		edge_id;
	size_t		head_id;
	t_list		*out_edges;

	out_edges = *node_out_edges(flow_graph, node_id);
	while (out_edges)
	{
		edge_id = LST_CONT(out_edges, size_t);
		if (try_relaxation(flow_graph, node_id, edge_id))
		{
			head_id = edge_head(flow_graph, edge_id);
			if (!in_queue[head_id])
			{
				queue_push(queue, list_new(&head_id, sizeof(size_t)));
				in_queue[head_id] = 1;
			}
		}
		out_edges = out_edges->next;
	}
}

static int	detect_cycle(t_graph *flow_graph, size_t node_id)
{
	size_t	max_length;

	max_length = flow_graph->nodes.length - 1;
	if (node_flow_data(flow_graph, node_id)->path_length > max_length)
		return (1);
	return (0);
}

int			min_path(t_graph *flow_graph, size_t source)
{
	t_list	*pop;
	t_queue	queue;
	char	*in_queue;

	if (!(in_queue = ft_memalloc(flow_graph->nodes.length)))
		return (-1);
	queue_init(&queue);
	queue_push(&queue, list_new(&source, sizeof(size_t)));
	in_queue[source] = 1;
	while (queue.size > 0)
	{
		pop = queue_pop(&queue);
		in_queue[LST_CONT(pop, size_t)] = 0;
		if (detect_cycle(flow_graph, LST_CONT(pop, size_t)))
			break ;
		explore_neighbors(flow_graph, &queue, in_queue, LST_CONT(pop, size_t));
		list_del(&pop, free_stub);
	}
	free(in_queue);
	list_del(&pop, free_stub);
	queue_destroy(&queue, free_stub);
	return (0);
}
