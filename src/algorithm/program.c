/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/12 12:34:47 by aamadori         ###   ########.fr       */
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

static void	pull_single_ant(t_colony_node_data *tail_data,
					t_colony_node_data *head_data, t_path *path)
{
	if ((tail_data->flags & START) && !head_data)
	{
		tail_data->ant = 0;
		path->ants = 0;
		path->running_ants = 0;
	}
	else if (!head_data)
	{
		tail_data->ant = 0;
		path->running_ants--;
	}
	else if ((tail_data->flags & START))
	{
		head_data->ant = tail_data->ant;
		tail_data->ant--;
		path->ants--;
		path->running_ants++;
	}
	else
		head_data->ant = tail_data->ant;
}

static void	pull_ants(t_graph *graph, t_path *path)
{
	size_t				head_id;
	size_t				tail_id;
	t_colony_node_data	*head_data;
	t_colony_node_data	*tail_data;
	t_list				*node_list;

	tail_id = path->node;
	tail_data = node_colony_data(graph, tail_id);
	head_data = NULL;
	while (!(tail_data->flags & START))
	{
		if (tail_data->ant)
			pull_single_ant(tail_data, head_data, path);
		head_id = tail_id;
		head_data = tail_data;
		tail_id = tail_data->ancestor;
		tail_data = node_colony_data(graph, tail_id);
	}
	pull_single_ant(tail_data, head_data, path);
}

int		generate_line(t_lemin *info, t_list *paths, t_array *program)
{
	t_path	curr;
	int		incomplete;

	incomplete = 0;
	while (paths)
	{
		curr = LST_CONT(paths, t_path);
		if (curr.running_ants + curr.ants > 0)
		{
			incomplete = 1;
			pull_ants(&info->graph, &curr);
		}
		paths = paths->next;
	}
	return (incomplete);
}

void	output_program(t_lemin *info)
{
	t_array	program;
	t_list	*paths;

	array_init(&program, sizeof(t_instruction));
	init_ants(info);
	paths = init_paths(info);
	repartition_ants(info, paths);
	while (generate_line(info, paths, &program))
	{
		print_line(info, &program);
		array_clear(&program, NULL);
	}
	array_clear(&program, NULL);
	list_del(&paths, free_stub);
}
