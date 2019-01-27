/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/27 16:27:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include "array.h"

size_t	(*g_func_table[])(char*) = {
	is_nbr_ants,
	is_start,
	is_end,
	is_command,
	is_comment,
	is_node,
	is_edge
};

void	init_nodes_and_edges(t_graph *graph)
{
	graph->nodes.ptr = NULL;
	graph->nodes.elem_size = sizeof(t_node);
	graph->nodes.length = 0;
	graph->nodes.reserved = 0;

	graph->edges.ptr = NULL;
	graph->edges.elem_size = sizeof(t_edge);
	graph->edges.length = 0;
	graph->edges.reserved = 0;
}

ssize_t	check_special_flags(t_lemin *info, ssize_t flags, ssize_t success)
{
	if (info->f_start == 0 && success != l_edge)
		flags |= L_START;
	if (info->f_end == 0 && success != l_edge)
    	flags |= L_END;
	if (info->f_ants == 0 && (success == l_comment || success == l_command))
		flags |= L_ANTS;
	return (flags);
}

ssize_t			choose_flags2(t_lemin *info, ssize_t success)
{
	ssize_t flags;

	flags = 0;
	if (success == l_command)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(info, flags, success);
	}
	else if (success == l_comment)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(info, flags, success);
	}
	else if (success == l_node)
	{
		flags = L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
		flags = check_special_flags(info, flags, success);
	}
	else if (success == l_edge)
	{
		flags = L_COMMAND | L_COMMENT | L_EDGE;
		flags = check_special_flags(info, flags, success);
	}
	return (flags);
}
ssize_t			choose_flags(t_lemin *info, ssize_t success)
{
	ssize_t	flags;

	flags = 0;
	if (success == l_ants && info->f_ants == 0)
	{
		info->f_ants = 1;
		flags = L_START | L_END | L_COMMAND | L_COMMENT | L_NODE | L_EDGE;
	}
	else if (success == l_start && info->f_start == 0)
	{
		info->f_start = 1;
		flags = L_NODE;
	}
	else if (success == l_end && info->f_end == 0)
	{
		info->f_end = 1;
		flags = L_NODE;
	}
	else
		flags = choose_flags2(info, success);
	return (flags);
}

ssize_t				check_input(t_lemin *info, char *line, ssize_t flags)
{
	ssize_t	flags_reset;
	ssize_t	index;
	ssize_t	ret;

	ret = 0;
	index = 0;
	flags_reset = flags;
	while (index < 7)
	{
		flags = flags_reset;
		if (((flags = flags >> index & 1) && g_func_table[index](line)))
		{
			ret = store_input(info, index, line);
			return (ret);
		}
		index++;
	}
	return (FAIL);
}

ssize_t			parse_input(t_lemin *info)
{
	char		*line;
	ssize_t		flags;
	ssize_t		ret;


	ft_bzero(info, sizeof(t_lemin));
	info->max_x_coord = INT_MIN;
	info->min_x_coord = INT_MAX;
	info->max_y_coord = INT_MIN;
	info->min_y_coord = INT_MAX;
	ret = 0;
	init_nodes_and_edges(&(info->graph));
	flags = L_ANTS | L_COMMAND | L_COMMENT;
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags);
		free(line);
		if (ret > -1)
			flags = choose_flags(info, ret);
		else
			return (0);
	}
	if (info->f_start == 0 || info->f_end == 0 || info->f_ants == 0)
		return (0);
	/* TODO ret = is_map_valid(info); */
	return (ret);
}
