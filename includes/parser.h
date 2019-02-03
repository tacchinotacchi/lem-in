/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:00:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 23:12:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lem-in.h"
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
# define STATE_START 0b1
# define STATE_END 0b10
# define STATE_ANTS 0b100
# define FAIL -1

typedef enum	s_success
{
	l_ants = 0,
	l_start,
	l_end,
	l_command,
	l_comment,
	l_start_node,
	l_end_node,
	l_node,
	l_edge
}				t_success;

typedef struct	s_edge_pair
{
	size_t	minor;
	size_t	major;
}				t_edge_pair;

typedef struct	s_name_node
{
	char	*name;
	size_t	index;
}				t_name_node;

int		parse_input(t_lemin *info, int initial_flags);

/*return -1 for wrong inputs and return 'index' keep track of the type of input*/
int		check_input(t_lemin *info, char *line, int flags);

int		choose_flags(int *parser_state,  int success);
int		choose_flags2(int *parser_state, int success);

int		check_special_flag(t_lemin *info, int flags, int success);
void	init_colony_data(t_colony_node_data *data);
/*return -1 for error(malloc failure) return 'index' to keep track of the type
of input*/
int		store_input(t_lemin *info, int index, char *line);

int		is_map_valid(t_lemin *info); /*TODO map validity check*/


/* return 1 for right_input return 0 for wrong input*/
int		is_nbr_ants(char *line, t_lemin *info);
int		is_start(char *line, t_lemin *info);
int		is_end(char *line, t_lemin *info);
int		is_command(char *line, t_lemin *info);
int		is_comment(char *line, t_lemin *info);
int		is_start_node(char *line, t_lemin *info);
int		is_end_node(char *line, t_lemin *info);
int		is_node(char *line, t_lemin *info);
int		is_edge(char *line, t_lemin *info);
int		ft_str_is_digit(const char *str); /*TODO to libft */
int		store_ants(t_lemin *info, char *line, int index);
int		store_commands(t_lemin *info, char *line, int index);
int		store_comments(t_lemin *info, char *line, int index);
int		store_node_data(t_lemin *info, char *line, int index);
int		search_nodes(t_array *nodes, char *node);
int		store_edge_data(t_lemin *info, char *line, int index);
int		compare_names(const void *ptr1, const void *ptr2);
int		compare_edge(const void *ptr1, const void *ptr2);
int 	compare_coords(const void *data1, const void *data2);
void	error(t_lemin *info);


#endif
