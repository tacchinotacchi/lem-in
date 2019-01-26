/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_func1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:13:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/26 19:27:39 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

size_t  is_nbr_ants(char *line)
{
	if (ft_str_is_digit(line) && ft_atoi(line) > 0)
		return (1);
	return (0);
}

size_t  is_start(char *line)
{
	    if(!ft_strcmp("##start", line))
			return (1);
		return (0);
}

size_t  is_end(char *line)
{
	    if(!ft_strcmp("##end", line))
			return (1);
		return (0);
}

size_t  is_command(char *line)
{
	    if(line[0] == '#' && line[1] == '!')
		/*instructions for command must be specified to add condition*/
			return (1);
		return (0);
}
