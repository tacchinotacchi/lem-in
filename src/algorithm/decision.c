/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:28:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 11:39:50 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "kpath.h"
#include "lem-in.h"

/* TODO clear subdecisions */
void destroy_decision(t_decision *decision);

int		path_can_solve(t_path path, t_path_graph *snapshot, t_decision *decision)
{
	/* TODO stub */
	return (1);
}

void explore_decision(t_lemin *input, t_decision *decision)
{
	t_path	path;
	size_t	index;

	input->curr_decisions[input->decision_depth] = *decision;
	while (decision->subdecisions_count > 0)
	{
		path = next_acceptable_path(input, decision->snapshot, decision->candidates);
		index = 0;
		while (index < decision->subdecisions.length)
		{
			if (path_can_solve(path, decision->snapshot, (t_decision*)decision->subdecisions.ptr))
			{
				input->decision_depth++;
				explore_decision(input, (t_decision*)decision->subdecisions.ptr);
				input->decision_depth--;
			}
			index++;
		}
	}
	destroy_decision(decision);
}
