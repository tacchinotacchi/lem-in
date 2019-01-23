/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:38:17 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 15:51:51 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _K_PATH_H
# define _K_PATH_H
# include "adjacency_list.h"
# include "array.h"

typedef struct	s_path_data
{
	size_t	creation_time;
	size_t	node_on_path;
}				t_path_data;

typedef struct	s_path_graph
{
	int		ants;
	size_t	time_frame;
	t_array	*nodes;
	t_array *edges;
}				t_path_graph;

typedef struct	s_decision
{
	t_path_graph	*snapshot;
	t_pq			*candidates;
}				t_decision;

#endif
