/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidetrack_precompute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:36:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 15:09:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "lem-in.h"

static void swap_edges(t_list *first, t_list *second)
{
	void	*swap;
	size_t	swap_size;

	swap = first->content;
	swap_size = first->content_size;
	first->content = second->content;
	first->content_size = second->content_size;
	second->content = swap;
	second->content_size = swap_size;
}

void	sort_edges_by_weight(t_node *node)
{
	t_list	*sorted;
	t_list	*traverse;
	int		min_value;
	t_list	*min;

	/* TODO merge/heap sort */
	sorted = node->out_edges;
	while (sorted->next)
	{
		traverse = sorted->next;
		min_value = ((t_edge_data*)((t_edge*)traverse->content)->data)->weight;
		min = traverse;
		while (traverse)
		{
			if (((t_edge_data*)((t_edge*)
				traverse->content)->data)->weight < min_value)
			{
				min_value = ((t_edge_data*)
					((t_edge*)traverse->content)->data)->weight;
				min = traverse;
			}
			traverse = traverse->next;
		}
		swap_edges(sorted, min);
		sorted = sorted->next;
	}
}

void	sort_all_edges(t_graph *graph)
{
	size_t index;

	index = 0;
	while (index < graph->nodes.length)
	{
		sort_edges_by_weight(&((t_node*)graph->nodes.ptr)[index]);
		index++;
	}
}

void	sidetrack_precompute(t_graph *graph)
{
	size_t	index;
	size_t	head;
	size_t	tail;
	int		head_weight;
	int		tail_weight;

	index = 0;
	while (index < graph->edges.length)
	{
		head = ((t_edge*)graph->edges.ptr)->head;
		tail = ((t_edge*)graph->edges.ptr)->tail;
		head_weight = ((t_colony_data*)((t_node*)graph->nodes.ptr)
			[head].data)->bfs_weight;
		tail_weight = ((t_colony_data*)((t_node*)graph->nodes.ptr)
			[tail].data)->bfs_weight;
		if (head_weight < 0	|| tail_weight < 0)
			((t_edge_data*)((t_node*)graph->edges.ptr)
				[index].data)->weight = -1;
		else
			((t_edge_data*)((t_node*)graph->edges.ptr)
				[index].data)->weight = head_weight - tail_weight + 1;
		index++;
	}
}
