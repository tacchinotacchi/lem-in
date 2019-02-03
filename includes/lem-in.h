/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 21:54:50 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LEM_IN_H
# define _LEM_IN_H
# include "list.h"
# include "adjacency_list.h"
# include "libft.h"
# include "tree.h"

# define START 0b1
# define END 0b10
# define GOAL 0b100

typedef struct	s_colony_node_data
{
	char	*name;
	int		flags;
	size_t	flow_in_id;
	size_t	flow_out_id;
	int		x;
	int		y;
	uint64_t	coord;
	size_t	ant;
}				t_colony_node_data;

typedef struct	s_colony_edge_data
{
	size_t	flow_id;
	int		in_use;
}				t_colony_edge_data;

typedef	struct	s_instruction
{
	size_t	ant_id;
	size_t	node_id;
	int		flusher;
}				t_instruction;

typedef struct 	s_lemin
{
	size_t		ants;
	t_graph		graph;
	t_list		*comments;
	t_list		*commands;
	size_t		start;
	size_t		end;
	int			max_x_coord;
	int			min_x_coord;
	int			max_y_coord;
	int			min_y_coord;
	t_tree		*coord_tree;
}				t_lemin;

void	get_ants(t_lemin *info);
void	init_nodes_and_edges(t_graph *graph);
void	get_start_data(t_lemin *info);
void	get_end_data(t_lemin *info);
void	get_node_data(t_lemin *info, char **split, int flags);
void	get_edge_data(t_lemin *info, char **split);
void	error(t_lemin *info);
ssize_t	search_nodes(t_array *nodes, char *node);
t_colony_node_data	*node_colony_data(const t_graph *graph, size_t id);
t_colony_edge_data	*edge_colony_data(const t_graph *graph, size_t id);
void	free_stub(void *ptr, size_t stub);
int		generate_line(t_lemin *info, t_array *program);
void	print_program(t_lemin *info, t_array *program);
int		init_ants(t_lemin *info);

#endif
