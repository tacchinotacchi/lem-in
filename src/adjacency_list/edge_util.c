/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:47:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/24 14:50:22 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"

/* TODO find another way to propagate error, turn to size_t */
ssize_t	edge_head(const t_graph *graph, size_t index)
{
	return (((t_edge*)graph->edges.ptr)[index].head);
}

ssize_t edge_tail(const t_graph *graph, size_t index)
{
	return (((t_edge*)graph->edges.ptr)[index].tail);
}
