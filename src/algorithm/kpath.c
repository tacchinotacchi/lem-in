/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:43:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 19:48:16 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "kpath.h"
#include "lem-in.h"

int		pseudotree_cmp(void *data1, void *data2);

void	unmark(t_lemin *input, t_path_graph *snapshot, size_t path_id)
{
	size_t	graph_id;
	t_edge	*parent_edge;
	int		last_node;

	last_node = 0;
	while (!last_node)
	{
		if (node_out_edges(snapshot->graph, path_id))
			last_node = 1;
		graph_id = (node_path_data(snapshot->graph, path_id))->graph_id;
		(node_colony_data(&input->graph, graph_id))->marked_decision = -1;
		(node_colony_data(&input->graph, graph_id))->marked_path_id = -1;
		if (!last_node)
		{
			parent_edge = node_out_edges(snapshot->graph, path_id)->content;
			path_id = edge_head(snapshot->graph, parent_edge->head);
		}
	}
}

t_path	next_acceptable_path(t_lemin *input,
			t_path_graph *snapshot, t_pq *candidates)
{
	t_node	*best;
	t_list	*trav_path;
	t_path	path;
	int		path_found;

	path_found = 0;
	best = NULL;
	snapshot->time_frame++;
	while (!path_found && check_empty_pq(candidates))
	{
		best = pop_pq(candidates, pseudotree_cmp);
		path.dev_node = walk_up_tree(input, snapshot, &path, ((t_path_data*)best->data)->pseudotree_id); /* go to start, marking, return deviation node in path */
		prune_path(input, snapshot, &path, ((t_path_data*)best->data)->pseudotree_id); /* go to end, not marking */
		trav_path = path.nodes;
		path_found = 1;
		while (trav_path->next)
		{
			if (mark_node(input, snapshot, *(size_t*)trav_path->content)) /* report conflict inside */
			{
				path_found = 0;
				unmark(input, snapshot, *(size_t*)trav_path->prev->content); /* unmark all parents, this should not have been marked by mark() */
				break ;
			}
			explore_sidetracks(input, snapshot, candidates, *(size_t*)trav_path->content);
			trav_path = trav_path->next;
		}
		free(best);
	}
	path.rank = snapshot->time_frame;
	path.path_tree = snapshot->graph;
	return ((path_found) ? path : (t_path){NULL, NULL, 0, -1});
}
