/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:28:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/23 16:51:47 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "kpath.h"
#include "lem-in.h"

void destroy_decision(t_decision *decision);

void explore_decision(t_lemin *input, t_decision *decision)
{
	t_list	*traverse;
	t_path	path;

	input->curr_decisions[input->decision_depth] = *decision;
	input->decision_depth++;
	while (decision->subdecisions)
	{
		path = next_acceptable_path(input, decision->snapshot, decision->candidates);
		traverse = decision->subdecisions;
		while (traverse)
		{
			if (path_can_solve(path, decision->snapshot, traverse->content))
				explore_decision(input, traverse->content);
			traverse = traverse->next;
		}
	}
	input->decision_depth--;
	destroy_decision(decision);
}
