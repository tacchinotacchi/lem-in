/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 06:46:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 06:46:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"

void		free_flow_nodes(void *ptr)
{
	t_node	*node;
	t_flow_node_data *data;

	node = ptr;
	data = node->data;
	free(data);
	list_del(&node->out_edges, free_stub);
	list_del(&node->in_edges, free_stub);
}
