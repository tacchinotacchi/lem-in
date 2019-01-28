/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 23:02:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/27 23:47:30 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "algorithm.h"
#include "lem-in.h"

t_colony_data		*node_colony_data(const t_graph *graph, size_t id)
{
	return (((t_node*)graph->nodes.ptr)[id].data);
}

t_flow_node_data	*node_flow_data(const t_graph *graph, size_t id)
{
	return (((t_node*)graph->nodes.ptr)[id].data);
}

t_flow_edge_data	*edge_flow_data(const t_graph *graph, size_t id)
{
	return (((t_edge*)graph->edges.ptr)[id].data);
}
