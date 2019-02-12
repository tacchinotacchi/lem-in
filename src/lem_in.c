/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/12 19:03:52 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "ft_printf.h"
#include "lem_in.h"

static t_program	try_flows(t_lemin *info)
{
	t_graph		flow_graph;
	t_program	program;
	t_program	test_program;
	size_t		flow;
	int			first_time;

	transform_graph(&info->graph, &flow_graph);
	first_time = 1;
	array_init(&program.instr, 1);
	while (first_time || flow > 0)
	{
		flow = min_cost_flow(&flow_graph,
			node_colony_data(&info->graph, info->start)->flow_out_id,
			node_colony_data(&info->graph, info->end)->flow_in_id,
			first_time ? info->ants : flow);
		interpret_flow(info, &flow_graph);
		first_time = 0;
		test_program = output_program(info);
		if (first_time || test_program.flushers < program.flushers)
		{
			array_clear(&program.instr, NULL);
			program = test_program;
		}
		else
			array_clear(&test_program.instr, NULL);
		if (test_program.flushers > program.flushers)
			break ;
		flow = ft_min(program.flow_used, flow - 1);
	}
	free_flow_graph(&flow_graph);
	return (program);
}

int			main(void)
{
	t_lemin		info;
	t_program	best_program;

	if (parse_input(&info, 0) < 0)
	{
		free_parser(&info);
		ft_dprintf(2, "ERROR\n");
		return (0);
	}
	best_program = try_flows(&info);
	ft_putchar('\n');
	output_program(&info);
	print_program(&info, &best_program.instr);
	array_clear(&best_program.instr, NULL);
	free_lemin(&info);
	return (0);
}
