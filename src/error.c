/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:47:08 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/31 17:25:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "lem-in.h"

void		ft_assert(int cond, const char *message,
				const char *file, const char *line)
{
	if (!cond)
	{
		ft_printf("%s at %s:%s");
		exit(0);
	}
}

static void	free_comments(void *ptr, size_t content_size)
{
	(void)content_size;
	/* TODO initialize all variables */
	free(ptr);
}

static void	free_nodes(void *ptr)
{
	if ((t_colony_node_data*)((t_node*)ptr)->data)
	{
		if (((t_colony_node_data*)((t_node*)ptr)->data)->name)
			free(((t_colony_node_data*)((t_node*)ptr)->data)->name);
		free((t_colony_node_data*)((t_node*)ptr)->data);
	}
	list_del(&(((t_node*)ptr)->out_edges), free_stub);
	list_del(&(((t_node*)ptr)->in_edges), free_stub);
}

static void	free_edges(void *ptr)
{
	(void)ptr;
}

void		error(t_lemin *info)
{
	array_clear(&(info->graph.nodes), free_nodes);
	array_clear(&(info->graph.edges), free_edges);
	list_del(&(info->comments), free_comments);
}
