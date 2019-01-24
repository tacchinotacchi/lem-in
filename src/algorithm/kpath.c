/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:43:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 16:34:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "kpath.h"
#include "lem-in.h"

int		pseudotree_cmp(void *data1, void *data2);

void	unmark(t_lemin *input, t_path_graph *snapshot, size_t path_index)
{
	size_t	graph_index;
	t_edge	*parent_edge;
	int		last_node;

	last_node = 0;
	while (!last_node)
	{
		if (node_out_edges(snapshot->graph, path_index))
			last_node = 1;
		graph_index = (node_path_data(snapshot->graph, path_index))->graph_id;
		(node_colony_data(&input->graph, graph_index))->in_use_by = -1;
		if (!last_node)
		{
			parent_edge = node_out_edges(snapshot->graph, path_index)->content;
			path_index = edge_head(snapshot->graph, parent_edge->head);
		}
	}
}

t_path	next_acceptable_path(t_lemin *input,
			t_path_graph *snapshot, t_pq *candidates)
{
	t_node	*best;
	t_list	*dev_path;
	t_path	path;
	int		path_found;

	path_found = 0;
	best = NULL;
	snapshot->time_frame++;
	while (!path_found && check_empty_pq(candidates))
	{
		/* TODO while dev_path doesn't have conflicts */
		/* TODO priority_queue by copy: void *pop_pq(candidates, cmp) returns*/
		best = pop_pq(candidates, pseudotree_cmp);
		dev_path = walk_up_tree(input, snapshot, &path, ((t_path_data*)best->data)->pseudotree_id); /* go to start, marking, return deviation node in path */
		path.dev_node = *(size_t*)dev_path->content;
		prune_path(input, snapshot, &path, ((t_path_data*)best->data)->pseudotree_id); /* go to end, not marking */
		path_found = 1;
		while (dev_path->next)
		{
			if (mark_node(input, snapshot, *(size_t*)dev_path->content)) /* report conflict inside */
			{
				path_found = 0;
				unmark(input, snapshot, *(size_t*)dev_path->prev->content); /* unmark all parents, this should not have been marked by mark() */
				break ;
			}
			explore_sidetracks(input, snapshot, candidates, *(size_t*)dev_path->content);
			dev_path = dev_path->next;
		}
		free(best);
	}
	path.rank = snapshot->time_frame;
	path.path_tree = snapshot->graph;
	return ((path_found) ? path : (t_path){NULL, NULL, 0, -1});
}
