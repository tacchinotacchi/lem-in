/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:27:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 15:29:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"

static void		animate_ant(t_renderer *renderer,
					size_t prev_node, t_instruction instr)
{
	GLuint	endpoints[2];

	renderer->animation_time = 0.f;
	endpoints[0] = prev_node;
	endpoints[1] = instr.node_id;
	array_push_back(&renderer->ant_data, endpoints);
}

static ssize_t	instruction_is_valid(t_lemin *info, t_instruction instr)
{
	t_colony_node_data	*node_data;
	t_list				*traverse;

	traverse = *node_in_edges(&info->graph, instr.node_id);
	while (traverse)
	{
		node_data = node_colony_data(&info->graph,
			edge_tail(&info->graph, LST_CONT(traverse, size_t)));
		if ((node_data->flags & START) || node_data->ant == instr.ant_id)
			return (edge_tail(&info->graph, LST_CONT(traverse, size_t)));
		traverse = traverse->next;
	}
	return (-1);
}

static ssize_t	execute_instruction(t_lemin *info, t_instruction instruction)
{
	t_colony_node_data	*node_data;
	ssize_t				prev_node;

	node_data = node_colony_data(&info->graph, instruction.node_id);
	prev_node = -1;
	if (((node_data->flags & END) || node_data->ant == 0)
		&& (prev_node = instruction_is_valid(info, instruction)) >= 0)
	{
		ft_printf("%sInstruction valid%s: ant %zu to %s\n",
			ANSI_COLOR_GREEN, ANSI_COLOR_RESET,
			instruction.ant_id, node_data->name);
		node_data->ant = instruction.ant_id;
		node_colony_data(&info->graph, prev_node)->ant = 0;
	}
	else
		ft_printf("%sInstruction invalid%s: ant %zu to %s\n",
			ANSI_COLOR_RED, ANSI_COLOR_RESET,
			instruction.ant_id, node_data->name);
	return (prev_node);
}

void			execute_line(t_lemin *info, t_renderer *renderer, char animate)
{
	t_instruction		instruction;
	t_list				*pop;
	ssize_t				prev_node;

	if (animate)
	{
		if (renderer->animation_time < 1.f)
			return ;
		renderer->ant_data.length = 0;
	}
	ft_printf("%s---NEW LINE---%s\n", ANSI_COLOR_CYAN, ANSI_COLOR_RESET);
	pop = list_pop(&info->instructions);
	while (pop && !LST_CONT(pop, t_instruction).flusher)
	{
		instruction = LST_CONT(pop, t_instruction);
		if ((prev_node = execute_instruction(info, instruction)) < 0)
			return ;
		if (animate)
			animate_ant(renderer, prev_node, instruction);
		pop = list_pop(&info->instructions);
	}
	free(pop);
}
