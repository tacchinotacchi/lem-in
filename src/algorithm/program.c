/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/12 17:08:49 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "algorithm.h"
#include "ft_printf.h"

void	print_instruction(t_lemin *info, t_array *program, size_t index)
{
	t_instruction	*instr;

	instr = ((t_instruction*)program->ptr);
	if (instr[index].flusher)
		ft_printf("\n");
	else
	{
		ft_printf("L%zu-%s%s", instr[index].ant_id,
			node_colony_data(&info->graph, instr[index].node_id)->name,
			(index + 1 < program->length && !instr[index + 1].flusher) ?
				" " : "");
	}
}

void	print_line(t_lemin *info, t_array *program)
{
	size_t		index;

	index = 0;
	while (index < program->length)
		print_instruction(info, program, index++);
}

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

int		generate_line(t_lemin *info, t_list *paths, t_array *program)
{
	t_path			*curr;
	t_instruction	flusher;
	int				incomplete;

	incomplete = 0;
	while (paths)
	{
		curr = paths->content;
		if (curr->running_ants + curr->ants > 0)
		{
			incomplete = 1;
			pull_ants(info, curr, program);
		}
		paths = paths->next;
	}
	if (incomplete)
		flusher = (t_instruction){0, 0, 1};
	array_push_back(program, &flusher);
	return (incomplete);
}

void	output_program(t_lemin *info)
{
	t_array	program;
	t_list	*paths;

	array_init(&program, sizeof(t_instruction));
	init_ants(&info->graph, info->ants);
	paths = init_paths(info);
	repartition_ants(paths, info->ants);
	while (generate_line(info, paths, &program))
	{
		print_line(info, &program);
		array_clear(&program, NULL);
	}
	array_clear(&program, NULL);
	list_del(&paths, free_stub);
}
