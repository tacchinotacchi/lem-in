/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:13:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/30 14:12:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

size_t  is_nbr_ants(char *line, t_lemin *info)
{
	(void)info;
	if (ft_str_is_digit(line) && ft_atoi(line) > 0)
		return (1);
	return (0);
}

size_t  is_start(char *line, t_lemin *info)
{
		(void)info;
		if(!ft_strcmp("##start", line))
			return (1);
		return (0);
}

size_t  is_end(char *line, t_lemin *info)
{
		(void)info;
		if(!ft_strcmp("##end", line))
			return (1);
		return (0);
}

size_t  is_command(char *line, t_lemin *info)
{
		(void)info;
		if(line[0] == '#' && line[1] == '!')
		/*instructions for command must be specified to add condition*/
			return (1);
		return (0);
}
