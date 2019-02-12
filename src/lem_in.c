/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/12 10:37:55 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "ft_printf.h"
#include "lem_in.h"

int			main(void)
{
	t_lemin		info;
	t_graph		flow_graph;

	if (parse_input(&info, 0) < 0)
	{
		free_parser(&info);
		ft_dprintf(2, "ERROR\n");
		return (0);
	}
	transform_graph(&info.graph, &flow_graph);
	min_cost_flow(&flow_graph,
		node_colony_data(&info.graph, info.start)->flow_out_id,
		node_colony_data(&info.graph, info.end)->flow_in_id,
		info.ants);
	if (interpret_flow(&info, &flow_graph) < 1)
		ft_dprintf(2, "ERROR\n");
	else
	{
		ft_putchar('\n');
		output_program(&info);
	}
	free_lemin(&info);
	free_flow_graph(&flow_graph);
	return (0);
}
