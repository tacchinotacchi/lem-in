/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/27 16:13:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "ft_printf.h"
#include "lem_in.h"

static int			try_new(t_lemin *info, t_program *min)
{
	t_program	test;

	test = output_program(info);
	if (test.flow_used
		&& (!min->instr.length || test.flushers < min->flushers))
	{
		array_clear(&min->instr, NULL);
		*min = test;
	}
	else
		array_clear(&test.instr, NULL);
	if (!test.flow_used
			|| (min->instr.length && test.flushers > min->flushers))
		return (0);
	return (1);
}

static t_program	try_flows(t_lemin *info)
{
	t_graph		flow_graph;
	t_program	min;

	array_init(&min.instr, sizeof(t_instruction));
	min.flow_used = 0;
	transform_graph(&info->graph, &flow_graph);
	while (increase_flow(&flow_graph,
		node_colony_data(&info->graph, info->start)->flow_out_id,
		node_colony_data(&info->graph, info->end)->flow_in_id))
	{
		interpret_flow(info, &flow_graph);
		if (!try_new(info, &min))
			break ;
	}
	free_flow_graph(&flow_graph);
	return (min);
}

int					main(void)
{
	t_lemin		info;
	t_program	best_program;

	if (parse_input(&info, 0) == -1)
	{
		free_lemin(&info);
		ft_dprintf(2, "ERROR\n");
		return (0);
	}
	best_program = try_flows(&info);
	ft_putchar('\n');
	if (best_program.flow_used)
		print_program(&info, &best_program.instr);
	else
		ft_dprintf(2, "ERROR\n");
	array_clear(&best_program.instr, NULL);
	free_lemin(&info);
	return (0);
}
