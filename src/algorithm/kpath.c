/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:43:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 17:51:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"unmark
#include "kpath.h"
#include "lem-in.h"

int		pseudotree_cmp(void *data1, void *data2)
{
	t_path_data	*node1;
	t_path_data	*node2;

	node1 = data1;
	node2 = data2;
	return (node1->cost - node2->cost);
}

void	unmark(t_lemin *input, t_path_graph *snapshot, size_t path_id)
{
	size_t	graph_id;
	t_edge	*parent_edge;

	while (node_out_edges(snapshot->graph, path_id))
	{
		parent_edge = node_out_edges(snapshot->graph, path_id)->content;
		path_id = edge_head(snapshot->graph, parent_edge->head);s
		graph_id = (node_path_data(snapshot->graph, path_id))->graph_id;
		(node_colony_data(&input->graph, graph_id))->marked_decision = -1;
		(node_colony_data(&input->graph, graph_id))->marked_path_id = -1;
	}
}

t_path	next_acceptable_path(t_lemin *input,
			t_path_graph *snapshot, t_pq *candidates)
{
	t_path_data	*best;
	t_list		*trav_path;
	t_path		path;
	int			path_found;
	int			dev_node_passed;

	path_found = 0;
	best = NULL;
	dev_node_passed = 0;
	while (!path_found && check_empty_pq(candidates))
	{
		best = pop_pq(candidates, pseudotree_cmp);
		path.dev_node = walk_up_tree(input, snapshot, &path, best->pseudotree_id);
		prune_path(input, snapshot, &path, best->pseudotree_id);
		trav_path = path.nodes;
		path_found = 1;
		while (trav_path->next)
		{
			if (mark_node(input, snapshot, *(size_t*)trav_path->content))
			{
				path_found = 0;
				unmark(input, snapshot, *(size_t*)trav_path->prev->content);
				break ;
			}
			if (path.dev_node = *(size_t*)trav_path->content)
				dev_node_passed = 1;
			if (dev_node_passed)
				explore_sidetracks(input, snapshot, candidates, *(size_t*)trav_path->content);
			trav_path = trav_path->next;
		}
		snapshot->time_frame++;
		free(best);
	}
	path.rank = snapshot->time_frame;
	path.path_tree = snapshot->graph;
	return ((path_found) ? path : (t_path){NULL, NULL, 0, -1});
}
