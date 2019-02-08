/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 17:34:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "ft_printf.h"
#include "lem_in.h"

static void	output_program(t_lemin *info)
{
	t_array	program;

	array_init(&program, sizeof(t_instruction));
	init_ants(info);
	while (generate_line(info, &program))
	{
		print_program(info, &program);
		array_clear(&program, NULL);
	}
	/* TODO is this call needed? */
	array_clear(&program, NULL);
}

int			main(void)
{
	t_lemin		info;
	t_graph		flow_graph;

	if (parse_input(&info, L_ANTS | L_COMMENT | L_COMMAND) < 0)
	{
		parser_error(&info);
		ft_dprintf(2, "Error\n");
		return (0);
	}
	free_trees(&info);
	array_init(&flow_graph.nodes, sizeof(t_node));
	array_init(&flow_graph.edges, sizeof(t_edge));
	transform_graph(&info.graph, &flow_graph);
	min_cost_flow(&flow_graph,
		node_colony_data(&info.graph, info.start)->flow_out_id,
		node_colony_data(&info.graph, info.end)->flow_in_id,
		info.ants);
	interpret_flow(&info.graph, &flow_graph);
	/* TODO check the flow is at least 1 */
	ft_putchar('\n');
	output_program(&info);
	free_lemin(&info);
	free_flow_graph(&flow_graph);
	return (0);
}
