/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:47:08 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/26 19:13:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser.h"
#include "algorithm.h"

void		free_trees(t_lemin *info)
{
	tree_clear(&(info->coord_tree), free_stub);
	tree_clear(&(info->name_tree), free_t_name_node);
	tree_clear(&(info->edge_tree), free_stub);
}

static void	free_command(void *ptr, size_t stub_size)
{
	t_command	*cmd;

	(void)stub_size;
	cmd = ptr;
	ft_splitdel(cmd->args);
	free(cmd);
}

void		free_flow_graph(t_graph *flow_graph)
{
	array_clear(&(flow_graph->nodes), free_flow_nodes);
	array_clear(&(flow_graph->edges), free_edges);
}

void		free_lemin(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_stub);
	list_del(&info->commands, free_command);
	list_del(&info->instructions, free_stub);
}
