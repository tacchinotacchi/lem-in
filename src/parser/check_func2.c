/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 04:31:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/25 19:50:07 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

ssize_t	ft_str_is_digit(const char *str)
{
	ssize_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index] == 0))
			return (0);
	}
	return (1);
}

ssize_t	is_comment(char *line)
{
	if (line[0] == '#' && line[1] != '#') /*separation from comment*/
		return (1);
	return (0);
}

ssize_t	is_node(char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	if (line[0] != 'L' && line[0] != '#' && split[0] && split[1] && split[2] &&
	!split[3] && ft_str_is_digit(split[1]) && ft_str_is_digit(split[2]))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

ssize_t	is_edge(char *line)
{
	int		index;
	char	**split;

	split = ft_strsplit(line, ' ');
	if (split[0] && split[1] && !split[2] && ft_str_is_digit(split[0]) &&
	ft_str_is_digit(split[1]) && ft_strcmp(split[0], split[1]))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}