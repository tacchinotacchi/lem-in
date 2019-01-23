/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/23 19:05:22 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "get_next_line.h"
#include <stdio.h>

#define L_ANTS 0b1
#define L_START 0b10
#define L_END 0b100
#define L_COMMAND 0b1000
#define L_COMMENT 0b10000
#define L_NODE 0b100000
#define L_EDGE 0b1000000

size_t	is_nbr_ants(char *line);
size_t	is_start(char *line);
size_t	is_end(char *line);
size_t	is_command(char *line);
size_t	is_comment(char *line);
size_t	is_node(char *line);
size_t	is_edge(char *line);

size_t	(*g_func_table[])(char*) = {
	is_nbr_ants,
	is_start,
	is_end,
	is_command,
	is_comment,
	is_node,
	is_edge
};

size_t	choose_flags(size_t line_index)
{
	/*TODO turn off or turn on flags regarding which line has been read or which test were failed*/
	return (flags);
}

size_t	turn_off_flags(size_t f_index);
{
	return (flags);
}

int		check_input(char *line, size_t flags, size_t line_index)
{
	size_t	flags;
	size_t	index;

	//	1		1		1		1		1		1		1
	//	edge	node	comment	command	end		start	ants	
	flags = L_ANTS | L_COMMANDS | L_COMMENTS;
	while (f_index < 7)
	{
		if (((flags = flags >> index) & 1) && g_func_table[index](line))
		{
			store_input();
			return (TYPE_OF_SUCESS);
		}
		index++;
	}
	return (FAIL);
}

int		parse_input(t_lemin *info)
{
	char	*line;
	size_t	line_index;
	size_t	flags;

	input_index = 0;
	while (get_next_line(0, &line) > 0)
	{
		check_input(line, flags, line_index);
		free(line);
		flags = choose_flags(line_index);
		line_index++;
	}
	return (0);
}

int		main(void)
{
	t_lemin info;

	ft_bzero(&info, sizeof(t_lemin));
	parse_input(&info);
	return (0);
}
