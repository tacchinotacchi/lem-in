/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 04:31:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/27 21:52:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	is_comment(char *line, t_lemin *info)
{
	(void)info;
	if (line[0] == '#' && line[1] != '#') /*separation from comment*/
		return (1);
	return (0);
}

size_t	is_node(char *line, t_lemin *info)
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
	if (line[0] != 'L' && line[0] != '#' && cnt == 3 &&
	ft_str_is_digit(split[1]) && ft_str_is_digit(split[2])
	&& content_cmp(&(info->graph.nodes), split))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

size_t	is_start_node(char *line, t_lemin *info)
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
	if (line[0] != 'L' && line[0] != '#' && cnt == 3 &&
	ft_str_is_digit(split[1]) && ft_str_is_digit(split[2])
	&& content_cmp(&(info->graph.nodes), split))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

size_t	is_end_node(char *line, t_lemin *info)
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
	if (line[0] != 'L' && line[0] != '#' && cnt == 3 &&
	ft_str_is_digit(split[1]) && ft_str_is_digit(split[2])
	&& content_cmp(&(info->graph.nodes), split))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}

size_t	is_edge(char *line, t_lemin *info)
{
	int		cnt;
	char	**split;

	(void)info;
	if (!(split = ft_strsplit(line, '-')))
	{	
		ft_splitdel(split);
		return (0);
	}
	cnt = 0;
	while (split[cnt])
		cnt++;
	if (cnt == 2 && ft_str_is_digit(split[0]) &&
	ft_str_is_digit(split[1]) && ft_strcmp(split[0], split[1]))
	{
		ft_splitdel(split);
		return (1);
	}
	ft_splitdel(split);
	return (0);
}