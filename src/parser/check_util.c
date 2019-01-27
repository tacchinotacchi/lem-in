/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:29:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/27 21:59:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	content_cmp(t_array *nodes, char **split)
{
	size_t	index;

	index = 0;
	while (index < nodes->length)
	{
		if ( !ft_strcmp(((t_colony_data*)((t_node*)nodes->ptr)[index].data)->name, split[0]) ||
		(((t_colony_data*)((t_node*)nodes->ptr)[index].data)->x == ft_atoi(split[1]) &&
		((t_colony_data*)((t_node*)nodes->ptr)[index].data)->y == ft_atoi(split[2])) )
			return (0);
		index++;
	}
	return (1);	
}

size_t	ft_str_is_digit(const char *str)
{
	ssize_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index] == 0))
			return (0);
		index++;
	}
	return (1);
}
