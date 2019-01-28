/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:06:06 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/28 17:30:03 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "lem-in.h"

static void	free_stub(void *ptr, size_t stub)
{
	(void)stub;
	free(ptr);
}

static int	try_relaxation(t_graph *flow_graph, t_list *curr, t_list *edge)
{
	t_flow_edge_data	*edge_data;
	t_flow_node_data	*curr_data;
	t_flow_node_data	*next_data;

	edge_data = edge_flow_data(flow_graph, LST_CONT(edge, size_t));
	if (edge_data->flow >= edge_data->capacity)
		return (0);
	curr_data = node_flow_data(flow_graph, LST_CONT(curr, size_t));
	next_data = node_flow_data(flow_graph,
		edge_head(flow_graph, LST_CONT(edge, size_t)));
	if (curr_data->path_cost + edge_data->weight < next_data->path_cost)
	{
		next_data->path_cost = curr_data->path_cost + edge_data->weight;
		next_data->ancestor = LST_CONT(curr, size_t);
		next_data->path_length = curr_data->path_length + 1;
		return (1);
	}
	return (0);
}

static int	detect_cycle(t_graph *flow_graph, size_t id)
{
	/* TODO is it length or length - 1 */
	size_t	max_length;

	max_length = flow_graph->nodes.length - 1;
	if (node_flow_data(flow_graph, id)->path_length > max_length)
		return (1);
	return (0);
}

static int	put_in_queue(t_graph *flow_graph, t_list **queue,
				char *in_queue, t_list *edge)
{
	size_t	head;

	head = edge_head(flow_graph, LST_CONT(edge, size_t));
	in_queue[head] = 1;
	list_add(queue, list_new(&head, sizeof(size_t)));
	return (0);
}

int		min_path(t_lemin *info, t_graph *flow_graph)
{
	t_list	*queue;
	t_list	*curr_id;
	t_list	*edge_traverse;
	char	*in_queue;

	queue = NULL;
	list_add(&queue,
		list_new(&node_colony_data(&info->graph, info->start)->flow_out_id,
			sizeof(size_t)));
	in_queue = ft_memalloc(flow_graph->nodes.length * sizeof(char));
	in_queue[node_colony_data(&info->graph, info->start)->flow_out_id] = 1;
	while (queue)
	{
		curr_id = list_pop(&queue);
		if (detect_cycle(flow_graph, LST_CONT(curr_id, size_t)))
			break ;
		in_queue[LST_CONT(curr_id, size_t)] = 0;
		edge_traverse = *node_out_edges(flow_graph, LST_CONT(curr_id, size_t));
		while (edge_traverse)
		{
			if (try_relaxation(flow_graph, curr_id, edge_traverse))
				put_in_queue(flow_graph, &queue, in_queue, edge_traverse);
			edge_traverse = edge_traverse->next;
		}
		list_del(&curr_id, free_stub);
	}
	free(in_queue);
	list_del(&queue, free_stub);
	return (0);
}

int		min_cost_flow(t_lemin *info, t_graph *flow_graph, int flow)
{

}
