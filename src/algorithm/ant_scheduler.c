/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_scheduler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 00:19:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/26 19:40:47 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"

static size_t	evaluate_cost(t_path path, size_t current_cost)
{
	if (path.length == 0)
		return (0);
	return (path.length + path.ants - current_cost);
}

static size_t	make_choice(t_list *paths, size_t current_cost)
{
	t_list	*traverse;
	t_list	*min;
	size_t	traverse_cost;
	size_t	min_cost;

	min = NULL;
	traverse = paths;
	while (traverse)
	{
		traverse_cost = evaluate_cost(LST_CONT(traverse, t_path),
			current_cost);
		if (!min || traverse_cost < min_cost)
		{
			min_cost = traverse_cost;
			min = traverse;
		}
		traverse = traverse->next;
	}
	LST_CONT(min, t_path).ants++;
	return (min_cost);
}

void			repartition_ants(t_list *paths, size_t ants)
{
	size_t	allocated_ants;
	size_t	total_cost;

	allocated_ants = 0;
	total_cost = 0;
	while (allocated_ants < ants)
	{
		total_cost = make_choice(paths, total_cost);
		allocated_ants++;
	}
}
