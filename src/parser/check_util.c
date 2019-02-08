/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:29:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 15:28:14 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_str_is_digit(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '+')
			index++;
		else if (!ft_isdigit(str[index]))
			return (0);
		else
			index++;
	}
	return (1);
}

int		compare_coords(const void *data1, const void *data2)
{
	if (*(uint64_t*)data1 > *(uint64_t*)data2)
		return (1);
	else if (*(uint64_t*)data1 == *(uint64_t*)data2)
		return (0);
	else
		return (-1);
}

int		compare_names(const void *data1, const void *data2)
{
	return (ft_strcmp(((t_name_node*)data1)->name, \
	((t_name_node*)data2)->name));
}

int		compare_edge(const void *ptr1, const void *ptr2)
{
	const t_edge_pair	*pair1;
	const t_edge_pair	*pair2;

	pair1 = ptr1;
	pair2 = ptr2;
	if (pair1->major != pair2->major)
		return (pair1->major - pair2->major);
	return (pair1->minor - pair2->minor);
}
