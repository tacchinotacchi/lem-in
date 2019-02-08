/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:31:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 15:28:24 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"

void	add_node(t_graph *graph, void *data, size_t data_size)
{
	t_node new_node;

	new_node.in_edges = 0;
	new_node.out_edges = 0;
	new_node.data = malloc(data_size);
	if (new_node.data)
	{
		ft_memcpy(new_node.data, data, data_size);
		array_push_back(&graph->nodes, &new_node);
	}
}

void	add_edge(t_graph *graph, size_t tail, size_t head, size_t data_size)
{
	t_edge	edge;
	size_t	index;

	edge.tail = tail;
	edge.head = head;
	edge.data = ft_memalloc(data_size);
	array_push_back(&graph->edges, &edge);
	index = graph->edges.length - 1;
	list_add(node_out_edges(graph, tail), list_new(&index, sizeof(size_t)));
	list_add(node_in_edges(graph, head), list_new(&index, sizeof(size_t)));
}
