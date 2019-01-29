/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/29 16:35:49 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "lem-in.h"

int	main(void)
{
	t_lemin 	info;
	t_graph		flow_graph;
	t_array		program;

	parse_input(&info, L_ANTS | L_COMMENT);
	array_init(&flow_graph.nodes, sizeof(t_node));
	array_init(&flow_graph.edges, sizeof(t_edge));
	transform_graph(&info.graph, &flow_graph);
	min_cost_flow(&flow_graph,
		node_colony_data(&info.graph, info.start)->flow_out_id,
		node_colony_data(&info.graph, info.end)->flow_in_id,
		0);
	interpret_flow(&info.graph, &flow_graph);
	array_init(&program, sizeof(t_instruction));
	init_ants(&info);
	while (list_length(node_colony_data(&info.graph, info.end)->ants) < info.ants)
		generate_line(&info, &program);
	print_program(&info, &program);
	return (0);
}
