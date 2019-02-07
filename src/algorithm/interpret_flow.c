/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_flow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:05:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 01:38:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "algorithm.h"

int		interpret_flow(t_graph *input, t_graph *flow_graph)
{
	size_t	colony_id;
	size_t	flow_id;
	size_t	tail_id;
	size_t	head_id;

	colony_id = 0;
	while (colony_id < input->edges.length)
	{
		tail_id = edge_tail(input, colony_id);
		head_id = edge_head(input, colony_id);
		if (!(node_colony_data(input, head_id)->flags & START)
			&& !(node_colony_data(input, tail_id)->flags & END))
		{
			flow_id = edge_colony_data(input, colony_id)->flow_id;
			edge_colony_data(input, colony_id)->in_use =
				edge_flow_data(flow_graph, flow_id)->flow;
		}
		colony_id++;
	}
	return (0);
}
