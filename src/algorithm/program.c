/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 00:19:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "ft_printf.h"

void	print_instruction(t_lemin *info, t_array *program, size_t index)
{
	t_instruction	*instr;

	instr = ((t_instruction*)program->ptr);
	if (instr[index].flusher)
		ft_printf("\n");
	else
	{
		ft_printf("L%zu-%s%s", instr[index].ant_id,
			node_colony_data(&info->graph, instr[index].node_id)->name,
			(index + 1 < program->length && !instr[index + 1].flusher) ?
				" " : "");
	}
}

void	print_program(t_lemin *info, t_array *program)
{
	size_t		index;

	index = 0;
	while (index < program->length)
		print_instruction(info, program, index++);
}
