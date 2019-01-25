/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 05:28:10 by jaelee           ###   ########.fr       */
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

size_t	choose_flags2(t_lemin *info, size_t success)
{
	size_t flags;

	flags = 0;
	if (success == l_command)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_speical_node(info, flags);
	}
	else if (success == l_comment)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_speical_node(info, flags);
	}
	else if (success == l_node)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_speical_node(info, flags);
	}
	else if (success == l_edge)
	{
		flags = L_COMMAND | L_COMMENT | L_EDGE;
		flags = check_speical_node(info, flags);
	}
	return (flags);
}
size_t	choose_flags(t_lemin *info, size_t success)
{
	size_t	flags;

	flags = 0;
	if (success == l_ants)
		flags = L_START | L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	else if (success == l_start && info->start == 0)
	{
		info->start = 1;
		if (info->end == 0)
			flags = L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		else 
			flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	}
	else if (success == l_end && info->end == 0)
	{	
		info->end = 1;
		if (info->start == 0)
			flags = L_START | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		else
			flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	}
	else
		flags = choose_flags2(info, success);	
	return (flags);
}

int		check_input(t_lemin *info, char *line, size_t flags)
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
	size_t		flags;
	size_t		ret;

	ret = 0;
	flags = L_ANTS | L_COMMAND | L_COMMENT;
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags);
		free(line);
		if (ret > -1)
			flags = choose_flags(info, ret);
		else
			error(info);
	}
	if (info->start == 0 || info->end == 0)
		return (0);
	return (1);
}

int		main(void)
{
	t_lemin 	info;
	ft_bzero(&info, sizeof(t_lemin));
	parse_input(&info);
	return (0);
}
