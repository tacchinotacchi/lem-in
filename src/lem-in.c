/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:30:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/28 12:04:29 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "algorithm.h"
#include "lem-in.h"

int	main(void)
{
	t_lemin 	info;
	t_graph		flow_graph;

	parse_input(&info, L_ANTS | L_COMMENT);
	array_init(&flow_graph.nodes, sizeof(t_node));
	array_init(&flow_graph.edges, sizeof(t_edge));
	transform_graph(&info.graph, &flow_graph);
	return (0);
}
