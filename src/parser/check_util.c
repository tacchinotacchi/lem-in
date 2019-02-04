/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:29:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/04 21:50:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_str_is_digit(const char *str)
{
	ssize_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '+')
			index++;
		else if (ft_isdigit(str[index] == 0))
			return (0);
		else
			index++;
	}
	return (1);
}

int		compare_coords(const void *data1, const void *data2)
{
	if (*(uint64_t*)data1 > *(uint64_t*)data2)
		return(1);
	else if (*(uint64_t*)data1 == *(uint64_t*)data2)
		return (0);
	else
		return (-1);
}

int		compare_names(const void *data1, const void *data2)
{
	return (ft_strcmp(((t_name_node*)data1)->name,
	((t_name_node*)data2)->name));
}
