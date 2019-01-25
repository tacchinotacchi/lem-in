/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 03:21:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

size_t	(*g_func_table[])(char*) = {
	is_nbr_ants,
	is_start,
	is_end,
	is_command,
	is_comment,
	is_node,
	is_edge
};

size_t	choose_flags(size_t line_index, size_t success)
{
	size_t	flags;

	flags = 0;
	if (success == l_ants)
		flags = L_START | L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	if (success == l_start || success == l_end)
	{
		if (success == l_start)
			flags = L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	}
	else if (success == l_end)
		flags = L_START
	else if (success == l_command)
	else if (success == l_comment)
	else if (success == l_node)
	else if (success == l_edge)
	return (flags);
}

int		check_input(t_lemin *info, char *line, size_t flags, size_t line_index)
{
	size_t	flags;
	size_t	index;
	size_t	ret;

	ret = 0;
	while (index < 7)
	{
		if (((flags = flags >> index) & 1) && g_func_table[index](line))
		{
			ret = store_input(info, index, line);
			return (ret);
		}
		index++;
	}
	return (FAIL);
}

int		parse_input(t_lemin *info)
{
	char		*line;
	size_t		line_index;
	size_t		flags;
	size_t		ret;

	line_index = 0;
	ret = 0;
	flags = L_ANTS | L_COMMAND | L_COMMENT;
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags, line_index);
		free(line);
		if (ret > -1)
			flags = choose_flags(line_index, ret);
		else
			error(info);
		line_index++;
	}
	return (0);
}

int		main(void)
{
	t_lemin 	info;
	ft_bzero(&info, sizeof(t_lemin));
	parse_input(&info);
	return (0);
}
