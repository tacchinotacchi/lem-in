/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:05:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 17:39:24 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"

long	interpret_flow(t_lemin *info, t_graph *flow_graph)
{
	long	flow_out;
	size_t	colony_id;
	size_t	flow_id;
	size_t	tail_id;
	size_t	head_id;

	flow_out = 0;
	colony_id = 0;
	while (colony_id < info->graph.edges.length)
	{
		tail_id = edge_tail(&info->graph, colony_id);
		head_id = edge_head(&info->graph, colony_id);
		if (!(node_colony_data(&info->graph, head_id)->flags & START)
			&& !(node_colony_data(&info->graph, tail_id)->flags & END))
		{
			flow_id = edge_colony_data(&info->graph, colony_id)->flow_id;
			edge_colony_data(&info->graph, colony_id)->in_use =
				edge_flow_data(flow_graph, flow_id)->flow;
		}
		if ((node_colony_data(&info->graph, tail_id)->flags & START)
			&& edge_colony_data(&info->graph, colony_id)->in_use)
			flow_out++;
		colony_id++;
	}
	return (flow_out);
}
