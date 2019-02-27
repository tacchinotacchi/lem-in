/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 22:47:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/27 16:16:34 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ALGORITHM_H
# define _ALGORITHM_H

# include "adjacency_list.h"

enum				e_edge_type
{
	e_normal = 0,
	e_back
};

typedef struct		s_flow_node_data
{
	size_t	colony_id;
	size_t	ancestor;
	long	path_cost;
	long	potential;
	long	path_max_flow;
	size_t	path_length;
	long	flags;
}					t_flow_node_data;

typedef struct		s_flow_edge_data
{
	long				capacity;
	long				flow;
	long				weight;
	size_t				inverse;
	size_t				colony_id;
	enum e_edge_type	type;
}					t_flow_edge_data;

typedef struct		s_path
{
	size_t	node;
	size_t	length;
	size_t	ants;
	size_t	running_ants;
}					t_path;

t_flow_node_data	*node_flow_data(const t_graph *graph, size_t id);
t_flow_edge_data	*edge_flow_data(const t_graph *graph, size_t id);
void				node_data_init(t_flow_node_data *node_data);
void				edge_data_init(t_flow_edge_data *edge_data,
						long weight, char inverse);
int					transform_graph(t_graph *input, t_graph *flow_graph);
int					min_path(t_graph *flow_graph, size_t source);
int					increase_flow(t_graph *flow_graph,
						size_t source, size_t sink);
void				repartition_ants(t_list *paths, size_t ants);
size_t				walk_back(t_graph *graph, size_t node_id);
void				sort_paths(t_list **paths);

#endif
