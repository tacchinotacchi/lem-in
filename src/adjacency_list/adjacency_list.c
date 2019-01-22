/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:31:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 01:33:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"

void	add_node(t_graph* graph, void *data, size_t data_size)
{
	t_node new_node;

	new_node.edges = 0;
	new_node.data = malloc(data_size);
	if (new_node.data)
	{
		ft_memcpy(new_node.data, data, data_size);
		array_push_back(&graph->nodes, &new_node);
	}
}

void	add_edge(t_graph* graph, ssize_t tail, ssize_t head)
{
	t_edge	edge_forward;
	t_edge	edge_backward;
	ssize_t	index;

	edge_forward.tail = tail;
	edge_forward.head = head;
	edge_forward.data = NULL;
	edge_backward.tail = head;
	edge_backward.head = tail;
	edge_forward.data = NULL;
	array_push_back(&graph->nodes, &edge_forward);
	array_push_back(&graph->nodes, &edge_backward);
	index = graph->nodes.length - 2;
	list_add(&((t_node*)graph->nodes.ptr)[tail].edges,
		list_new(&index, sizeof(ssize_t)));
	index = graph->nodes.length - 1;
	list_add(&((t_node*)graph->nodes.ptr)[head].edges,
		list_new(&index, sizeof(ssize_t)));
}
