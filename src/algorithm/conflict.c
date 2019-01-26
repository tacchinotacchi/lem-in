/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:35:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 16:19:21 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "kpath.h"
#include "lem-in.h"

int		mark_node(t_lemin *input, t_path_graph *snapshot, size_t path_id)
{
	size_t	graph_id;
	t_colony_data *node_data;

	graph_id = (node_path_data(snapshot->graph, path_id))->graph_id;
	node_data = node_colony_data(&input->graph, graph_id);
	if (!(node_data->flags & GOAL) && node_data->marked_decision >= 0)
		return (1);
	else if (!(node_data->flags & GOAL))
		node_reserve(input, node_path_data(snapshot->graph, path_id));
	return (0);
}
