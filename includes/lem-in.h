/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/27 21:53:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H
# include "list.h"
# include "adjacency_list.h"
# include "libft.h"
# include "kpath.h"

# define START 0b1
# define END 0b10
# define GOAL 0b100

typedef struct	s_colony_data
{
	char	*name;
	int		flags;
	int		x;
	int		y;
	int		bfs_weight;
	int		marked_decision;
	int		marked_path_id;
}				t_colony_data;

typedef struct	s_edge_data
{
	int		weight;
}				t_edge_data;

typedef struct 	s_lemin
{
	int			ants;
	int			f_start;
	int			f_end;
	int			f_ants;
	t_list		*comments;
	t_graph		graph;
	size_t		*start_nodes;
	t_path		*curr_paths;
	t_path		*best_solution;
	int			best_solution_instr;
	size_t		decision_depth;
	size_t		max_decision_depth;
	int			max_x_coord;
	int			min_x_coord;
	int			max_y_coord;
	int			min_y_coord;
}				t_lemin;

void	get_ants(t_lemin *info);
void	init_nodes_and_edges(t_graph *graph);
void	get_start_data(t_lemin *info);
void	get_end_data(t_lemin *info);
void	get_node_data(t_lemin *info, char **split, int flags);
void	get_edge_data(t_lemin *info, char **split);
void	error(t_lemin *info);
ssize_t	search_nodes(t_array *nodes, char *node);
/* TODO review and move to libft */
void	ft_splitdel(char **split);
t_colony_data	*node_colony_data(const t_graph *graph, size_t index);

#endif
