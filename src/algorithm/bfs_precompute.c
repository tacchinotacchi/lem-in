/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_precompute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 12:31:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 12:47:21 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "lem-in.h"

static void	free_stub(void *ptr, size_t size)
{
	(void)size;
	free(ptr);
}

static void	explore_neighbors(t_graph *graph,
	t_list **next_candidates, t_list *node)
{
	t_list	*edge_traverse;
	t_list	*new_candidate;

	edge_traverse = ((t_node*)graph->nodes.ptr)
						[*(ssize_t*)node->content].in_edges;
	while (edge_traverse)
	{
		new_candidate = list_new(&(((t_edge*)graph->edges.ptr)
			[*(ssize_t*)edge_traverse->content].head),
			sizeof(ssize_t));
		list_add(next_candidates, new_candidate);
		edge_traverse = edge_traverse->next;
	}
}

void	bfs_precompute(t_graph *graph, ssize_t end_node)
{
	t_list	*next_candidates;
	t_list	*candidates;
	t_list	*traverse;
	int		index;

	index = 0;
	list_add(&candidates, list_new(&end_node, sizeof(ssize_t)));
	while (candidates)
	{
		traverse = candidates;
		while (traverse)
		{
			((t_colony_data*)(((t_node*)graph->nodes.ptr)
				[*(ssize_t*)traverse->content].data))->bfs_weight = index;
			explore_neighbors(graph, &next_candidates, traverse);
			traverse = candidates->next;
		}
		list_del(&candidates, free_stub);
		candidates = next_candidates;
		index++;
	}
}
