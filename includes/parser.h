/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:00:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/27 17:08:20 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lem_in.h"
# include "array.h"
# define L_ANTS 0b1
# define L_START 0b10
# define L_END 0b100
# define L_COMMAND 0b1000
# define L_COMMENT 0b10000
# define L_START_NODE 0b100000
# define L_END_NODE 0b1000000
# define L_NODE 0b10000000
# define L_EDGE 0b100000000
# define L_INSTRUCTION 0b1000000000
# define STATE_START 0b1
# define STATE_END 0b10
# define STATE_ANTS 0b100
# define FAIL -1
# define FAIL_SOFT -2

enum			e_success
{
	l_ants = 0,
	l_start,
	l_end,
	l_command,
	l_comment,
	l_start_node,
	l_end_node,
	l_node,
	l_edge,
	l_instruction,
	l_max
};

typedef struct	s_flags_match
{
	int			flags_off;
	int			flags_on;
}				t_flags_match;

typedef struct	s_edge_pair
{
	size_t	major;
	size_t	minor;
}				t_edge_pair;

typedef struct	s_name_node
{
	char	*name;
	size_t	index;
}				t_name_node;

extern t_flags_match	g_flags_match[10];
extern int				(*const g_func_table[10])(char*);

int				parse_input(t_lemin *info, char visualizer);
int				check_input(t_lemin *info, char *line, int flags,
					int parser_state);
void			choose_flags(int *flags, int *parser_state, int success);
void			init_colony_data(t_colony_node_data *data);
int				store_input(t_lemin *info, int index, char *line);
int				is_nbr_ants(char *line);
int				is_start(char *line);
int				is_end(char *line);
int				is_command(char *line);
int				is_comment(char *line);
int				is_start_node(char *line);
int				is_end_node(char *line);
int				is_node(char *line);
int				is_edge(char *line);
int				is_instruction(char *line);
void			flags_turn_on(int *field, int bits);
void			flags_turn_off(int *field, int bits);
int				check_parser_state(int index, int parser_state);
int				ft_str_is_digit(const char *str);
int				store_ants(t_lemin *info, char *line, int index);
int				store_commands(t_lemin *info, char *line, int index);
int				store_comments(t_lemin *info, char *line, int index);
int				create_node_data(t_lemin *info, char *line, int index);
int				store_node_data(t_lemin *info, t_colony_node_data *data);
int				search_nodes(t_array *nodes, char *node);
int				store_edge_data(t_lemin *info, char *line, int index);
int				store_instruction(t_lemin *info, char *line, int index);
int				compare_names(const void *ptr1, const void *ptr2);
int				compare_edge(const void *ptr1, const void *ptr2);
int				compare_coords(const void *data1, const void *data2);
void			init_parser(t_lemin *info, int *parser_state, char visualizer);

#endif
