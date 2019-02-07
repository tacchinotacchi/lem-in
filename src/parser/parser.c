/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/07 14:11:05 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include "array.h"

int		(*g_func_table[])(char*) = {
	is_nbr_ants,
	is_start,
	is_end,
	is_command,
	is_comment,
	is_node,
	is_node,
	is_node,
	is_edge,
	is_instruction
};

t_flags_match	g_flags_match[] = {
	{L_ANTS, L_START | L_END | L_NODE | L_EDGE},
	{L_START | L_END | L_NODE | L_EDGE | L_INSTRUCTION, L_START_NODE},
	{L_START | L_END | L_NODE | L_EDGE | L_INSTRUCTION, L_END_NODE},
	{0, 0},
	{0, 0},
	{L_START_NODE, L_START | L_END | L_NODE | L_EDGE | L_INSTRUCTION},
	{L_END_NODE, L_START | L_END | L_NODE | L_EDGE | L_INSTRUCTION},
	{0, L_INSTRUCTION},
	{L_NODE | L_START | L_END, L_INSTRUCTION},
	{L_NODE | L_EDGE, 0}
};

void	choose_flags(int *flags, int *parser_state, t_success success)
{
	t_flags_match	match;

	match = g_flags_match[success];
	flags_turn_off(flags, match.flags_off);
	flags_turn_on(flags, match.flags_on);
	if (success == l_ants)
		*parser_state |= STATE_ANTS;
	else if (success == l_start)
		*parser_state |= STATE_START;
	else if (success == l_end)
		*parser_state |= STATE_END;
}

int		check_parser_state(int index, int parser_state)
{
	if (((1 << index) & L_START) && (parser_state & STATE_START))
		return (-1);
	if (((1 << index) & L_END) && (parser_state & STATE_END))
		return (-1);
	if (((1 << index) & L_ANTS) && (parser_state & STATE_ANTS))
		return (-1);
	return (0);
}

int		check_input(t_lemin *info, char *line, int flags, int parser_state)
{
	size_t	index;
	int		ret;

	ret = 0;
	index = 0;
	if (ft_strlen(line) == 0)
	{
		ft_putchar('\n');
		return (l_max);
	}
	while (index < sizeof(g_flags_match) / sizeof(g_flags_match[0]))
	{
		if ((((flags >> index) & 1) && g_func_table[index](line)))
		{
			if (check_parser_state(index, parser_state) < 0)
				return (FAIL);
			ft_putendl(line); /*must not print anything if there's error*/
			ret = store_input(info, index, line);
			return (ret);
		}
		index++;
	}
	return (FAIL);
}

void	init_lemin(t_lemin *info, int *parser_state, int *ret)
{
	ft_bzero(info, sizeof(t_lemin));
	info->max_x_coord = INT_MIN;
	info->min_x_coord = INT_MAX;
	info->max_y_coord = INT_MIN;
	info->min_y_coord = INT_MAX;
	array_init(&(info->graph.nodes), sizeof(t_node));
	array_init(&(info->graph.edges), sizeof(t_edge));
	*parser_state = 0;
	*ret = 0;
}

int		parse_input(t_lemin *info, int initial_flags)
{
	char	*line;
	int		flags;
	int		parser_state;
	int		ret;

	init_lemin(info, &parser_state, &ret);
	flags = initial_flags;
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags, parser_state);
		free(line);
		if (ret >= 0 && ret < l_max)
			choose_flags(&flags, &parser_state, ret);
		else if (ret < 0)
		{
			error(info);
			return (-1);
		}
	}
	if (parser_state != (STATE_ANTS | STATE_START | STATE_END))
	{
		error(info);
		return (-1);
	}
	return (ret);
}
