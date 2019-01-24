/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conflict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:35:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 17:56:52 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "kpath.h"
#include "lem-in.h"

int		mark_node(t_lemin *input, t_path_graph *snapshot, size_t path_id)
{
	size_t	graph_id;

	graph_id = (node_path_data(snapshot->graph, path_id))->graph_id;
	if ((node_colony_data(&input->graph, graph_id))->marked_decision >= 0)
	{
		/* TODO report conflict */;
	}
	else
		node_reserve(input, node_path_data(snapshot->graph, path_id));
	return (0);
}
