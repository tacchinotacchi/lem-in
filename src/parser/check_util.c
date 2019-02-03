/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:29:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 22:25:26 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_str_is_digit(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isdigit(str[index] == 0))
			return (0);
		index++;
	}
	return (1);
}
