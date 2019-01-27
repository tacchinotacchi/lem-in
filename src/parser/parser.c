/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/27 22:41:18 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include "array.h"

size_t	(*g_func_table[])(char*, t_lemin*) = {
	is_nbr_ants,
	is_start,
	is_end,
	is_command,
	is_comment,
	is_start_node,
	is_end_node,
	is_node,
	is_edge
};

ssize_t	check_special_flags(ssize_t *parser_state, ssize_t flags,
			ssize_t success)
{
	if ((*parser_state & STATE_START) == 0 && success != l_edge)
		flags |= L_START;
	if ((*parser_state & STATE_END) == 0 && success != l_edge)
    	flags |= L_END;
	if ((*parser_state & STATE_ANTS) == 0
		&& (success == l_comment || success == l_command))
		flags |= L_ANTS;
	return (flags);
}

ssize_t			choose_flags2(ssize_t *parser_state, ssize_t success)
{
	ssize_t flags;

	flags = 0;
	if (success == l_command)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(parser_state, flags, success);
	}
	else if (success == l_comment)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(parser_state, flags, success);
	}
	else if (success == l_node || success == l_start_node || success == l_end_node)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(parser_state, flags, success);
	}
	else if (success == l_edge)
	{
		flags = L_COMMAND | L_COMMENT | L_EDGE;
		flags = check_special_flags(parser_state, flags, success);
	}
	return (flags);
}
ssize_t			choose_flags(ssize_t *parser_state, ssize_t success)
{
	ssize_t	flags;

	flags = 0;
	if (success == l_ants && (*parser_state & STATE_ANTS) == 0)
	{
		*parser_state |= STATE_ANTS;
		flags = L_START | L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	}
	else if (success == l_start && (*parser_state & STATE_START) == 0)
	{
		*parser_state |= STATE_START;
		flags = L_START_NODE;
	}
	else if (success == l_end && (*parser_state & STATE_END) == 0)
	{
		*parser_state |= STATE_END;
		flags = L_END_NODE;
	}
	else
		flags = choose_flags2(parser_state, success);
	return (flags);
}

ssize_t			check_input(t_lemin *info, char *line, ssize_t flags)
{
	ssize_t	flags_reset;
	ssize_t	index;
	ssize_t	ret;

	ret = 0;
	index = 0;
	flags_reset = flags;
	while (index < 9)
	{
		flags = flags_reset;
		if (((flags = flags >> index & 1) && g_func_table[index](line, info)))
		{
			ret = store_input(info, index, line);
			return (ret);
		}
		index++;
	}
	return (FAIL);
}

ssize_t			parse_input(t_lemin *info, ssize_t initial_flags)
{
	char		*line;
	ssize_t		flags;
	ssize_t		parser_state;
	ssize_t		ret;


	ft_bzero(info, sizeof(t_lemin));
	info->max_x_coord = INT_MIN;
	info->min_x_coord = INT_MAX;
	info->max_y_coord = INT_MIN;
	info->min_y_coord = INT_MAX;
	array_init(&(info->graph.nodes), sizeof(t_node));
	array_init(&(info->graph.edges), sizeof(t_edge));
	ret = 0;
	parser_state = 0;
	flags = initial_flags;
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags);
		free(line);
		if (ret > -1)
			flags = choose_flags(&parser_state, ret);
		else
			return (0);
	}
	if (parser_state != (STATE_ANTS | STATE_START | STATE_END))
		return (0);
	/* TODO ret = is_map_valid(info); run BFS once to see the end is inside the list*/
	return (ret);
}
