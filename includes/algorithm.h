/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:47:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/28 19:34:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ALGORITHM_H
# define _ALGORITHM_H

#include "adjacency_list.h"

enum	e_edge_type
{
	e_normal = 0,
	e_back
};

typedef struct	s_flow_node_data
{
	size_t	colony_id;
	size_t	ancestor;
	size_t	path_length;
	long	path_cost;
	long	flags;
}				t_flow_node_data;

typedef struct	s_flow_edge_data
{
	long				capacity;
	long				flow;
	long				weight;
	size_t				inverse;
	enum e_edge_type	type;
	/* TODO weight implicit or explicit? */
}				t_flow_edge_data;

t_flow_node_data	*node_flow_data(const t_graph *graph, size_t id);
t_flow_edge_data	*edge_flow_data(const t_graph *graph, size_t id);
int					transform_graph(t_graph *input, t_graph *flow_graph);
int					min_path(t_graph *flow_graph, size_t source);

#endif
