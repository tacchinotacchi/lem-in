/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_modules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:49:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/27 17:07:54 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

int				(*const g_func_table[10])(char*) = {
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

t_flags_match	g_flags_match[10] = {
	{L_ANTS, L_START | L_END | L_NODE | L_EDGE},
	{L_START | L_END | L_NODE | L_EDGE, L_START_NODE},
	{L_START | L_END | L_NODE | L_EDGE, L_END_NODE},
	{0, 0},
	{0, 0},
	{L_START_NODE, L_START | L_END | L_NODE | L_EDGE},
	{L_END_NODE, L_START | L_END | L_NODE | L_EDGE},
	{0, 0},
	{L_NODE | L_START | L_END, 0},
	{L_NODE | L_EDGE, 0},
};

void			init_parser(t_lemin *info, int *parser_state, char visualizer)
{
	ft_bzero(info, sizeof(t_lemin));
	info->max_x_coord = INT_MIN;
	info->min_x_coord = INT_MAX;
	info->max_y_coord = INT_MIN;
	info->min_y_coord = INT_MAX;
	array_init(&(info->graph.nodes), sizeof(t_node));
	array_init(&(info->graph.edges), sizeof(t_edge));
	*parser_state = 0;
	if (visualizer)
	{
		g_flags_match[l_start].flags_off |= L_INSTRUCTION;
		g_flags_match[l_end].flags_off |= L_INSTRUCTION;
		g_flags_match[l_start_node].flags_on |= L_INSTRUCTION;
		g_flags_match[l_end_node].flags_on |= L_INSTRUCTION;
		g_flags_match[l_node].flags_on |= L_INSTRUCTION;
		g_flags_match[l_edge].flags_on |= L_INSTRUCTION;
	}
}

void			choose_flags(int *flags, int *parser_state, int success)
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
