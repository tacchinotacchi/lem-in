/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:47:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/27 23:46:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ALGORITHM_H
# define _ALGORITHM_H

#include "adjacency_list.h"

typedef struct	s_flow_node_data
{
	size_t	colony_id;
}				t_flow_node_data;

typedef struct	s_flow_edge_data
{
	int		capacity;
	int		flow;
	int		weight;
	/* TODO weight implicit or explicit? */
}				t_flow_edge_data;

t_flow_node_data	*node_flow_data(const t_graph *graph, size_t id);
t_flow_edge_data	*edge_flow_data(const t_graph *graph, size_t id);

#endif
