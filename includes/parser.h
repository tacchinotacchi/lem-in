/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:00:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/26 20:09:14 by jaelee           ###   ########.fr       */
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

ssize_t		parse_input(t_lemin *info);

/*return -1 for wrong inputs and return 'index' keep track of the type of input*/
ssize_t		check_input(t_lemin *info, char *line, ssize_t flags);

ssize_t		choose_flags(t_lemin *info,  ssize_t success);
ssize_t		choose_flags2(t_lemin *info, ssize_t success);

ssize_t		check_special_flag(t_lemin *info, ssize_t flags, ssize_t success);
void		init_colony_data(t_colony_data *data);
/*return -1 for error(malloc failure) return 'index' to keep track of the type
of input*/
ssize_t		store_input(t_lemin *info, ssize_t index, char *line);

ssize_t		is_map_valid(t_lemin *info); /*TODO map validity check*/


/* return 1 for right_input return 0 for wrong input*/
size_t		is_nbr_ants(char *line);
size_t		is_start(char *line);
size_t		is_end(char *line);
size_t		is_command(char *line);
size_t		is_comment(char *line);
size_t		is_start_node(char *line);
size_t		is_end_node(char *line);
size_t		is_node(char *line);
size_t		is_edge(char *line);

size_t		ft_str_is_digit(const char *str); /*TODO to libft */
void		ft_splitdel(char **split); /*TODO to libft */
void		init_nodes_and_edges(t_graph *graph); /*TODO to libft */
ssize_t		store_ants(t_lemin *info, char *line, ssize_t index);
ssize_t		store_commands(t_lemin *info, char *line, ssize_t index);
ssize_t		store_comments(t_lemin *info, char *line, ssize_t index);
ssize_t		store_node_data(t_lemin *info, char *line, ssize_t index);
ssize_t		search_nodes(t_array *nodes, char *node);
ssize_t		store_edge_data(t_lemin *info, char *line, ssize_t index);
void		error(t_lemin *info);


#endif