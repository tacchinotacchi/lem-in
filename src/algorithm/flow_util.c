/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 01:03:14 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/07 01:25:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.h"

void	node_data_init(t_flow_node_data *node_data)
{
	node_data->colony_id = 0;
	node_data->ancestor = 0;
	node_data->path_cost = INT_MAX;
	node_data->potential = 0;
	node_data->path_max_flow = INT_MAX;
	node_data->flags = 0;
}

void	edge_data_init(t_flow_edge_data *edge_data,
			long weight, char inverse)
{
	edge_data->capacity = inverse ? 0 : 1;
	edge_data->flow = 0;
	edge_data->weight = inverse ? -weight : weight;
	edge_data->type = inverse ? e_back : e_normal;
	edge_data->inverse = 0;
	edge_data->colony_id = 0;
}
