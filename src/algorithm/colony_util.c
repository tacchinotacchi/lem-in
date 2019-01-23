/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colony_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:05:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/23 15:09:00 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		node_flags(t_lemin *input, size_t index)
{
	return (((t_colony_data*)((t_node*)input->graph.nodes.ptr)->data)->flags);
}

int		node_weight(t_lemin *input, size_t index)
{
	return (((t_colony_data*)
		((t_node*)input->graph.nodes.ptr)->data)->bfs_weight);
}
