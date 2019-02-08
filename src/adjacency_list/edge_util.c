/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:47:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 15:27:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"

size_t	edge_head(const t_graph *graph, size_t index)
{
	return (((t_edge*)graph->edges.ptr)[index].head);
}

size_t	edge_tail(const t_graph *graph, size_t index)
{
	return (((t_edge*)graph->edges.ptr)[index].tail);
}
