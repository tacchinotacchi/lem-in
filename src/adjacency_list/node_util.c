/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:47:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/28 14:32:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"

t_list	**node_out_edges(const t_graph *graph, size_t index)
{
	return (&((t_node*)graph->nodes.ptr)[index].out_edges);
}

t_list	**node_in_edges(const t_graph *graph, size_t index)
{
	return (&((t_node*)graph->nodes.ptr)[index].in_edges);
}
