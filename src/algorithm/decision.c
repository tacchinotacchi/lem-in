/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:28:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 17:00:26 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "kpath.h"
#include "lem-in.h"

int		path_can_solve(t_path path, t_path_graph *snapshot, t_decision *decision)
{
	/* TODO stub */
	return (1);
}

void explore_decision(t_lemin *input)
{
	t_path_graph	*path_graph;
	t_pq			*candidates;
	t_path			path;
	size_t			index;
	int				null_tried;

	//input->curr_decisions[input->decision_depth] = *decision;
	null_tried = 0;
	init_path_graph(input, path_graph, candidates);
	input->decision_depth++;
	while (!null_tried)
	{
		path = next_acceptable_path(input, path_graph, candidates);
		if (!path)
			null_tried = 1;
		input->curr_paths[input->decision_depth] = path;
		if (input->decision_depth < input->max_decision_depth - 1)
			explore_decision(input);
		else
		{
			consider_solution(input);
			break;
		}
		/* TODO destroy path */
	}
	/* TODO destroy path_graph, candidates */
	input->decision_depth--;
}
