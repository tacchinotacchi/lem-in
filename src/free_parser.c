/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:12:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 22:45:35 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"

void	free_stub(void *ptr, size_t stub)
{
	(void)stub;
	free(ptr);
}

void	free_t_name_node(void *ptr, size_t content_size)
{
	t_name_node *data;

	(void)content_size;
	data = ptr;
	if (data->name)
		free(data->name);
	free(data);
}

void	free_nodes(void *ptr)
{
	t_node				*node;
	t_colony_node_data	*data;

	node = ptr;
	data = node->data;
	if (data->name)
		free(data->name);
	free(data);
	list_del(&node->out_edges, free_stub);
	list_del(&node->in_edges, free_stub);
}

void	free_edges(void *ptr)
{
	t_edge *edge;

	edge = ptr;
	free(edge->data);
}
