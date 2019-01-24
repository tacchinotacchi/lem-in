/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:28:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 18:54:46 by aamadori         ###   ########.fr       */
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
		path = next_acceptable_path(input, &decision->snapshot, decision->candidates);
		index = 0;
		/* TODO iterate over solutions solvable by deviation node */
		while (index < decision->subdecisions.length)
		{
			/*TODO mark subdecision as obsolete if it is */
			/*TODO if subdecision has been marked obsolete, remove reference */
			if (input->decision_depth == input->max_decision_depth)
			{
				input->decision_depth++;
				/* TODO save proposed solution to this decision before reporting solution and conflicts*/
				explore_decision(input, (t_decision*)decision->subdecisions.ptr + index);
				input->decision_depth--;
			}
			else
			{
				/* TODO report solution if we have reached max depth */;
			}
			index++;
		}
	}
	destroy_decision(decision);
}
