/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:00:17 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 03:08:20 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdio.h>
# include "lem-in.h"
# define L_ANTS 0b1
# define L_START 0b10
# define L_END 0b100
# define L_COMMAND 0b1000
# define L_COMMENT 0b10000
# define L_NODE 0b100000
# define L_EDGE 0b1000000
# define FAIL -1

typedef enum	s_success
{
	l_ants = 0,
	l_start,
	l_end,
	l_command,
	l_comment,
	l_node,
	l_edge
}				t_success;

int		parse_input(t_lemin *info);
int		check_input(char *line, size_t flags, size_t line_index);
size_t	choose_flags(size_t line_index, size_t success);
size_t	store_input(t_lemin *info, size_t index, char *line);

size_t	is_nbr_ants(char *line);
size_t	is_start(char *line);
size_t	is_end(char *line);
size_t	is_command(char *line);
size_t	is_comment(char *line);
size_t	is_node(char *line);
size_t	is_edge(char *line);

#endif