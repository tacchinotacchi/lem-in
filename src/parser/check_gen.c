/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:13:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/04 05:13:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

int  is_nbr_ants(char *line)
{
	if (ft_str_is_digit(line) && ft_atoi(line) > 0)
		return (1);
	return (0);
}

int  is_command(char *line)
{
		if(ft_strlen(line) >= 2 && line[0] == '#' && line[1] == '#'
			&& ft_strcmp(line, "##start") && ft_strcmp(line, "##end"))
			return (1);
		return (0);
}

int	is_comment(char *line)
{
	if (line[0] == '#'
		&& ((ft_strlen(line) > 1 && line[1] != '#') || ft_strlen(line) <= 1))
		return (1);
	return (0);
}
