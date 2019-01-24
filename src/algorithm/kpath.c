/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:43:01 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 11:38:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"
#include "kpath.h"
#include "lem-in.h"

int		pseudotree_cmp(void *data1, void *data2);

void	add_node_pseudo(t_path_graph *graph, size_t parent, size_t graph_id)
{
	ssize_t	already_there;

	already_there = node_present(graph, parent);
	if (already_there >= 0)
	{
		/* TODO update creation time */
	}
	else
	{
		/* TODO create node */
	}
}

t_path	next_acceptable_path(t_lemin *input,
			t_path_graph *snapshot, t_pq *candidates)
{
	t_node		best;
	t_path		path;
	t_list		*dev_path;
	int			path_found;

	path_found = 0;
	while (!path_found && check_empty_pq(candidates))
	{
		/* TODO while dev_path doesn't have conflicts */
		pop_pq(candidates, &best, pseudotree_cmp);
		dev_path = walk_up_tree(input, snapshot, &path, ((t_path_data*)best.data)->pseudotree_id); /* go to start, marking, return deviation node in path */
		path.dev_node = *(size_t*)dev_path->content;
		prune_path(input, snapshot, &path, ((t_path_data*)best.data)->pseudotree_id); /* go to end, not marking */
		path_found = 1;
		while (dev_path->next)
		{
			if (mark_node(input, snapshot, *(size_t*)dev_path->content)) /* report conflict inside */
			{
				path_found = 0;
				unmark(input, snapshot, *(size_t*)dev_path->content); /* unmark this and all parents */
				break ;
			}
			explore_sidetracks(input, snapshot, candidates, *(size_t*)dev_path->content);
			dev_path = dev_path->next;
		}
	}
	return ((path_found) ? path : (t_path){NULL, -1});
}
