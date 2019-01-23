/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:38:17 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/23 16:49:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _K_PATH_H
# define _K_PATH_H
# include "adjacency_list.h"
# include "array.h"
# include "priority_queue.h"

typedef struct s_lemin	t_lemin;

typedef struct	s_path_data
{
	t_list	*conflicts;
	size_t	creation_time;
	size_t	node_on_path;
	size_t	pseudotree_id;
	size_t	cost;
}				t_path_data;

typedef struct	s_path_graph
{
	size_t	time_frame;
	t_graph	*graph;
}				t_path_graph;

typedef struct	s_path
{
	t_list	*nodes;
	size_t 	dev_node;
	ssize_t	rank;
}				t_path;

t_path	next_acceptable_path(t_lemin *input,
			t_path_graph *snapshot, t_pq *candidates);

#endif
