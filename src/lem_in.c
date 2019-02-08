/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 06:35:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "lem_in.h"

int		main(void)
{
	t_lemin		info;
	t_graph		flow_graph;
	t_array		program;

	if (parse_input(&info, L_ANTS | L_COMMENT | L_COMMAND) < 0)
		return (0);
	ft_putchar('\n');
	free_trees(&info);
	array_init(&flow_graph.nodes, sizeof(t_node));
	array_init(&flow_graph.edges, sizeof(t_edge));
	transform_graph(&info.graph, &flow_graph);
	min_cost_flow(&flow_graph,
		node_colony_data(&info.graph, info.start)->flow_out_id,
		node_colony_data(&info.graph, info.end)->flow_in_id,
		info.ants);
	interpret_flow(&info.graph, &flow_graph);
	array_init(&program, sizeof(t_instruction));
	init_ants(&info);
	while (generate_line(&info, &program))
	{
		print_program(&info, &program);
		array_clear(&program, NULL);
	}
	free_all(&info, &flow_graph);
	return (0);
}
