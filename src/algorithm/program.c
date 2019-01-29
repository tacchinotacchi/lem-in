/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/29 17:09:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "ft_printf.h"

int		init_ants(t_lemin *info)
{
	size_t	ant_id;

	/* TODO clear all other nodes? */
	ant_id = 1;
	while (ant_id <= info->ants)
	{
		list_add(&(node_colony_data(&info->graph, info->start))->ants,
			list_new(&ant_id, sizeof(size_t)));
		ant_id++;
	}
	return (0);
}

void	absorb_ants(t_lemin *info, t_array *line, t_list **new_queue, size_t node_id)
{
	t_instruction instr;
	t_list	*pop;
	t_list	*edge_traverse;
	size_t	edge_id;
	size_t	next_id;

	edge_traverse = *node_in_edges(&info->graph, node_id);
	while (edge_traverse)
	{
		edge_id = LST_CONT(edge_traverse, size_t);
		if (edge_colony_data(&info->graph, edge_id)->in_use)
		{
			next_id = edge_tail(&info->graph, edge_id);
			list_add(new_queue, list_new(&next_id, sizeof(size_t)));
			if (node_colony_data(&info->graph, next_id)->ants)
			{
				pop = list_pop(&node_colony_data(&info->graph, next_id)->ants);
				list_add(&node_colony_data(&info->graph, node_id)->ants, pop);
				instr.ant_id = LST_CONT(pop, size_t);
				instr.node_id = node_id;
				instr.flusher = 0;
				array_push_back(line, &instr);
			}
		}
		edge_traverse = edge_traverse->next;
	}
}

void	generate_line(t_lemin *info, t_array *program)
{
	t_list	*pop;
	t_list	*new_queue;
	t_list	*node_queue;

	node_queue = NULL;
	list_add(&node_queue, list_new(&info->end, sizeof(size_t)));
	while (node_queue)
	{
		new_queue = NULL;
		while (node_queue)
		{
			pop = list_pop(&node_queue);
			/* TODO assert if node is not end but absorbs more than one ant */
			absorb_ants(info, program, &new_queue, LST_CONT(pop, size_t));
			list_del(&pop, free_stub);
		}
		node_queue = new_queue;
	}
	array_push_back(program, (t_instruction[]){{0, 0, 1}});
}

void	print_program(t_lemin *info, t_array *program)
{
	t_instruction	instr;
	size_t			index;

	index = 0;
	while (index < program->length)
	{
		instr = ((t_instruction*)program->ptr)[index];
		if (instr.flusher)
			ft_printf("\n");
		else
		{
			ft_printf("L%d-%s", instr.ant_id,
				node_colony_data(&info->graph, instr.node_id)->name);
			if (index + 1 < program->length
				&& !((t_instruction*)program->ptr)[index + 1].flusher)
				ft_printf(" ");
		}
		index++;
	}
}
