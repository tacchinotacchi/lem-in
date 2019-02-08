/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:47:08 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/08 06:22:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include "algorithm.h"

void		error(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_stub);
	tree_clear(&(info->coord_tree), free_stub);
	tree_clear(&(info->name_tree), free_t_name_node);
	tree_clear(&(info->edge_tree), free_stub);
}

void		free_trees(t_lemin *info)
{
	tree_clear(&(info->coord_tree), free_stub);
	tree_clear(&(info->name_tree), free_t_name_node);
	tree_clear(&(info->edge_tree), free_stub);

}

void		free_all(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_stub);
	/*TODO free commands and instructions*/
	/*TODO array_clear for flow_graph doesn't work T-T */
}
