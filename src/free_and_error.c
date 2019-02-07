/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:47:08 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/07 14:09:06 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lem-in.h"

void		free_stub(void *ptr, size_t stub)
{
	(void)stub;
	free(ptr);
}

static void	free_nodes(void *ptr)
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

static void	free_edges(void *ptr)
{
	t_edge *edge;

	edge = ptr;
	free(edge->data);
}

void		error(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_stub);
	tree_clear(&(info->coord_tree), free_stub);
}

void		free_all(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_stub);
	tree_clear(&(info->coord_tree), free_stub);
}
