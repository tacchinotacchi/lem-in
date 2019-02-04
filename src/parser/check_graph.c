/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 04:31:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/04 21:44:46 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_node(char *line)
{
	char	**split;
	int		cnt;

	if (!(split = ft_strsplit(line, ' ')))
	{
		ft_splitdel(split);
		return (0);
	}
	cnt = 0;
	while (split[cnt])
		cnt++;
	if (cnt == 3 && line[0] != 'L' && line[0] != '#' && !ft_strchr(line, '-')
		&& ft_str_is_digit(split[1]) && ft_str_is_digit(split[2]))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

int		is_edge(char *line)
{
	int		cnt;
	char	**split;

	if (!(split = ft_strsplit(line, '-')))
	{
		ft_splitdel(split);
		return (0);
	}
	cnt = 0;
	while (split[cnt])
		cnt++;
	if (cnt == 2 && ft_str_is_digit(split[0]) && ft_str_is_digit(split[1]))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

int		is_start(char *line)
{
	if (!ft_strcmp("##start", line))
		return (1);
	return (0);
}

int		is_end(char *line)
{
	if (!ft_strcmp("##end", line))
		return (1);
	return (0);
}
