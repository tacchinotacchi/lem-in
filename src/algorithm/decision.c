/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:28:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 20:49:37 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "kpath.h"
#include "priority_queue.h"
#include "lem-in.h"

int		init_path_graph(t_lemin *input, t_path_graph *path_graph, t_pq *candidates)
{
	t_path_data	path_data;

	path_graph->time_frame = 0;
	array_init(&path_graph->graph->nodes, sizeof(t_node));
	array_init(&path_graph->graph->edges, sizeof(t_edge));
	init_pq(candidates, sizeof(t_path_data));
	path_data.pseudotree_id = 0;
	path_data.creation_time = 0;
	path_data.graph_id = input->start_nodes[input->decision_depth];
	path_data.cost = 0;
	add_node(path_graph->graph, &path_data, sizeof(t_path_data));
	return (0);
}

void	consider_solution(t_lemin *input)
{
	size_t	index;
	int		instr;

	index = 0;
	while (index < input->max_decision_depth)
	{
		if (input->curr_paths[index].nodes
			&& (input->best_solution[index].nodes
				||input->curr_paths[index].cost < input->best_solution[index].cost))
			break;
		index++;
	}
	if (index < input->max_decision_depth)
	{
		instr = eval_solution(input);
		if (instr < input->best_solution_instr)
		{
			instr = input->best_solution_instr;
			copy_solution(input);
		}
	}
}

void	explore_decision(t_lemin *input)
{
	t_path_graph	path_graph;
	t_pq			candidates;
	t_path			path;
	int				null_tried;

	null_tried = 0;
	init_path_graph(input, &path_graph, &candidates);
	input->decision_depth++;
	while (!null_tried)
	{
		/* TODO set max path length as argument, return NULL first time a potential path exceeds it */
		path = next_acceptable_path(input, &path_graph, &candidates);
		if (!path.nodes)
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
