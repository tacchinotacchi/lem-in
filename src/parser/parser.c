/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:59:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/27 18:15:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include "get_next_line.h"
#include "array.h"

int				check_parser_state(int index, int parser_state)
{
	
	if ((index >= l_max)
		&& (parser_state ^ (STATE_START | STATE_END | STATE_ANTS)))
		return (-1);
	if (((1 << index) & L_START) && (parser_state & STATE_START))
		return (-1);
	if (((1 << index) & L_END) && (parser_state & STATE_END))
		return (-1);
	if (((1 << index) & L_ANTS) && (parser_state & STATE_ANTS))
		return (-1);
	return (0);
}

int				check_input(t_lemin *info, char *line,
					int flags, int parser_state)
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
			ft_putendl(line);
			ret = store_input(info, index, line);
			return (ret);
		}
		index++;
	}
	return (FAIL);
}

static int		fail_soft(int code, int visualizer, int parser_state)
{
	/* TODO l_max doesn't mean empty line, but unknown syntax */
	return ((visualizer == 0 && code >= l_max)
		|| (code < 0 && !check_parser_state(l_max, parser_state)));
}

int				parse_input(t_lemin *info, char visualizer)
{
	char	*line;
	int		flags;
	int		parser_state;
	int		ret;

	ret = 0;
	flags = L_ANTS | L_COMMENT | L_COMMAND;
	init_parser(info, &parser_state, visualizer);
	while (get_next_line(0, &line) > 0)
	{
		ret = check_input(info, line, flags, parser_state);
		free(line);
		if (ret >= 0 && ret < l_max)
			choose_flags(&flags, &parser_state, ret);
		/* TODO l_max doesn't mean empty line, but unknown syntax */
		else if (ret == FAIL || (visualizer == 0 && ret >= l_max))
		{
			line = NULL;
			break ;
		}
	}
	free(line);
	free_trees(info);
	if (parser_state != (STATE_ANTS | STATE_START | STATE_END))
		return (FAIL);
	return (fail_soft(ret, visualizer, parser_state) ? FAIL_SOFT : ret);
}
