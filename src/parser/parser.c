/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 22:27:22 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include "array.h"

int		(*g_func_table[])(char*, t_lemin*) = {
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

int	check_special_flags(int *parser_state, int flags,
			int success)
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

int			choose_flags2(int *parser_state, int success)
{
	int flags;

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
int			choose_flags(int *parser_state, int success)
{
	int	flags;

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

int			check_input(t_lemin *info, char *line, int flags)
{
	int	flags_reset;
	int	index;
	int	ret;

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

int			parse_input(t_lemin *info, int initial_flags)
{
	char		*line;
	int		flags;
	int		parser_state;
	int		ret;


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
	return (ret);
}
