/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colony_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:05:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 14:28:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		node_flags(const t_graph *graph, size_t index)
{
	return (((t_colony_data*)((t_node*)graph->nodes.ptr)->data)->flags);
}

int		node_weight(const t_graph *graph, size_t index)
{
	return (((t_colony_data*)
		((t_node*)graph->nodes.ptr)->data)->bfs_weight);
}

size_t	node_next_in_shortest(const t_graph *graph, size_t index)
{
	return (((t_colony_data*)
		((t_node*)graph->nodes.ptr)->data)->next_in_shortest);
}
