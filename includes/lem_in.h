/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/27 16:16:45 by aamadori         ###   ########.fr       */
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

typedef struct		s_colony_node_data
{
	char		*name;
	int			flags;
	size_t		flow_in_id;
	size_t		flow_out_id;
	int			x;
	int			y;
	uint64_t	coord;
	float		coords[3];
	float		accel[3];
	size_t		ant;
	size_t		ancestor;
	size_t		own_id;
}					t_colony_node_data;

typedef struct		s_colony_edge_data
{
	size_t	flow_id;
	int		in_use;
}					t_colony_edge_data;

typedef	struct		s_instruction
{
	size_t	ant_id;
	size_t	node_id;
	int		flusher;
}					t_instruction;

typedef struct		s_program
{
	t_array	instr;
	size_t	flushers;
	size_t	flow_used;
}					t_program;

typedef struct		s_command
{
	char	**args;
}					t_command;

typedef struct		s_lemin
{
	size_t		ants;
	t_graph		graph;
	t_list		*comments;
	t_list		*commands;
	t_list		*instructions;
	size_t		start;
	size_t		end;
	int			max_x_coord;
	int			min_x_coord;
	int			max_y_coord;
	int			min_y_coord;
	t_tree		*coord_tree;
	t_tree		*name_tree;
	t_tree		*edge_tree;
}					t_lemin;

void				get_ants(t_lemin *info);
void				init_nodes_and_edges(t_graph *graph);
void				get_start_data(t_lemin *info);
void				get_end_data(t_lemin *info);
void				get_node_data(t_lemin *info, char **split, int flags);
void				get_edge_data(t_lemin *info, char **split);
void				free_parser(t_lemin *info);
int					search_nodes(t_array *nodes, char *node);
t_colony_node_data	*node_colony_data(const t_graph *graph, size_t id);
t_colony_edge_data	*edge_colony_data(const t_graph *graph, size_t id);
long				interpret_flow(t_lemin *input, t_graph *flow_graph);
void				print_program(t_lemin *info, t_array *program);
t_program			output_program(t_lemin *info);
t_list				*init_paths(t_lemin *info);
int					init_ants(t_graph *graph, size_t ants);

void				free_stub(void *ptr, size_t stub);
void				free_t_name_node(void *ptr, size_t content_size);
void				free_nodes(void *ptr);
void				free_edges(void *ptr);
void				free_trees(t_lemin *info);
void				free_flow_nodes(void *ptr);
void				free_instructions(void *ptr);
void				free_lemin(t_lemin *info);
void				free_flow_graph(t_graph *flow_graph);

#endif
