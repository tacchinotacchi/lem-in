/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 22:18:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# include "list.h"
# include "adjacency_list.h"
# include "libft.h"
# include "kpath.h"

# define START 1
# define END 2
# define NODE 0

typedef struct	s_colony_data
{
	char	*name;
	int		flags;
	int		x;
	int		y;
	int		bfs_weight;
	int		in_use_by;
	t_list	*shortest_path; /* TODO set in bfs */
}				t_colony_data;

typedef struct	s_edge_data
{
	int		weight;
}				t_edge_data;

typedef struct	s_decision
{
	t_path_graph	*snapshot;
	t_pq			*candidates;
	t_array			subdecisions;
	size_t			subdecisions_count;
	int				obsolete;
}				t_decision;

typedef struct	s_solution
{
	t_list	*nodes_in_graph;
	t_list	*ranks;
}				t_solution;

typedef struct 	s_lemin
{
	int			ants;
	int			f_start;
	int			f_end;
	int			f_ants;
	t_list		*comments;
	t_graph		graph;
	t_decision	*curr_decisions;
	size_t		decision_depth;
	t_graph		*path_trees;
	t_list		*solutions;
}				t_lemin;

int		node_flags(t_lemin *input, size_t index);
int		node_weight(t_lemin *input, size_t index);

#endif
