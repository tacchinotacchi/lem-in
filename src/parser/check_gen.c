/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:13:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/09 16:38:22 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			is_nbr_ants(char *line)
{
	if (ft_str_is_digit(line) && ft_atoi(line) > 0)
		return (1);
	return (0);
}

int			is_command(char *line)
{
	if (ft_strlen(line) >= 2 && line[0] == '#' && line[1] == '#'
		&& ft_strcmp(line, "##start") && ft_strcmp(line, "##end"))
		return (1);
	return (0);
}

int			is_comment(char *line)
{
	if (line[0] == '#'
		&& ((ft_strlen(line) > 1 && line[1] != '#') || ft_strlen(line) <= 1))
		return (1);
	return (0);
}

static int	check_potential_instruction(const char *instr)
{
	char	**array;
	size_t	count;

	array = ft_strsplit(instr, '-');
	if (!array)
		return (-1);
	count = 0;
	while (array[count])
		count++;
	if (count == 2 && array[0][0] == 'L' && array[0][1] && array[1][0])
	{
		ft_splitdel(array);
		return (1);
	}
	ft_splitdel(array);
	return (0);
}

int			is_instruction(char *line)
{
	char	**array;
	size_t	index;
	int		result;

	array = ft_strsplit(line, ' ');
	if (!array)
		return (-1);
	if (!array[0])
	{
		ft_splitdel(array);
		return (0);
	}
	index = 0;
	while (array[index])
	{
		result = check_potential_instruction(array[0]);
		if (result != 1)
			break ;
		index++;
	}
	ft_splitdel(array);
	return (result);
}
