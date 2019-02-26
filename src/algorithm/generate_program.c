/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/26 19:46:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"

static void	pull_wave(t_colony_node_data *tail_data,
				t_colony_node_data *head_data, t_path *path, t_array *program)
{
	t_instruction	instr;

	instr.node_id = head_data->own_id;
	instr.flusher = 0;
	while (tail_data->ant != 0
		&& ((head_data->flags & END) || head_data->ant == 0))
	{
		instr.ant_id = tail_data->ant;
		array_push_back(program, &instr);
		if (head_data->flags & END)
			path->running_ants--;
		else
			head_data->ant = tail_data->ant;
		if (tail_data->flags & START)
		{
			tail_data->ant--;
			path->ants--;
			path->running_ants++;
		}
		else
			tail_data->ant = 0;
	}
}

static void	pull_ants(t_lemin *info, t_path *path, t_array *program)
{
	size_t				head_id;
	size_t				tail_id;
	t_colony_node_data	*head_data;
	t_colony_node_data	*tail_data;

	tail_id = path->node;
	tail_data = node_colony_data(&info->graph, tail_id);
	head_data = node_colony_data(&info->graph, info->end);
	while (!(tail_data->flags & START))
	{
		pull_wave(tail_data, head_data, path, program);
		head_id = tail_id;
		head_data = tail_data;
		tail_id = tail_data->ancestor;
		tail_data = node_colony_data(&info->graph, tail_id);
	}
	if (path->ants)
		pull_wave(tail_data, head_data, path, program);
}

static void	generate_flusher(t_program *program)
{
	t_instruction	flusher;

	flusher = (t_instruction){0, 0, 1};
	program->flushers++;
	array_push_back(&program->instr, &flusher);
}

void		generate_instructions(t_lemin *info, t_list *paths,
				t_program *program)
{
	t_path			*curr;
	t_list			*traverse;
	size_t			path_number;

	path_number = 1;
	while (path_number)
	{
		path_number = 0;
		traverse = paths;
		while (traverse)
		{
			curr = traverse->content;
			if (curr->running_ants + curr->ants > 0)
			{
				program->flow_used = ft_max(program->flow_used, ++path_number);
				pull_ants(info, curr, &program->instr);
			}
			traverse = traverse->next;
		}
		if (path_number)
			generate_flusher(program);
	}
}

t_program	output_program(t_lemin *info)
{
	t_program	program;
	t_list		*paths;

	array_init(&program.instr, sizeof(t_instruction));
	program.flushers = 0;
	program.flow_used = 0;
	init_ants(&info->graph, info->ants);
	paths = init_paths(info);
	repartition_ants(paths, info->ants);
	generate_instructions(info, paths, &program);
	list_del(&paths, free_stub);
	return (program);
}
