/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:41:40 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/30 20:00:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "ft_printf.h"

int		init_ants(t_lemin *info)
{
	size_t	node;

	node = 0;
	while (node < info->graph.nodes.length)
	{
		node_colony_data(&info->graph, node)->ant = 0;
		node++;
	}
	node_colony_data(&info->graph, info->start)->ant = info->ants;
	return (0);
}

int		absorb_ants(t_lemin *info, t_array *line, t_list **new_queue, size_t node_id)
{
	t_colony_node_data	*node_data;
	t_colony_node_data	*next_data;
	t_list	*edge_traverse;
	size_t	next_id;
	char	incomplete;

	incomplete = 0;
	edge_traverse = *node_in_edges(&info->graph, node_id);
	node_data = node_colony_data(&info->graph, node_id);
	while (edge_traverse)
	{
		if (edge_colony_data(&info->graph, LST_CONT(edge_traverse, size_t))->in_use)
		{
			next_id = edge_tail(&info->graph, LST_CONT(edge_traverse, size_t));
			next_data = node_colony_data(&info->graph, next_id);
			list_add(new_queue, list_new(&next_id, sizeof(size_t)));
			while (next_data->ant > 0)
			{
				incomplete = 1;
				node_data->ant = next_data->ant;
				if (next_data->flags & START)
					next_data->ant--;
				else
					next_data->ant = 0;
				array_push_back(line, (t_instruction[]){{
					.ant_id = node_data->ant,
					.node_id = node_id,
					.flusher = 0
				}});
				if (!(node_data->flags & END))
					break ;
			}
		}
		edge_traverse = edge_traverse->next;
	}
	return (incomplete);
}

int		generate_line(t_lemin *info, t_array *program)
{
	t_list	*pop;
	t_list	*new_queue;
	t_list	*node_queue;
	char	incomplete;

	node_queue = NULL;
	incomplete = 0;
	list_add(&node_queue, list_new(&info->end, sizeof(size_t)));
	while (node_queue)
	{
		new_queue = NULL;
		while (node_queue)
		{
			pop = list_pop(&node_queue);
			/* TODO assert if node is not end but absorbs more than one ant */
			incomplete |= absorb_ants(info, program, &new_queue, LST_CONT(pop, size_t));
			list_del(&pop, free_stub);
		}
		node_queue = new_queue;
	}
	array_push_back(program, (t_instruction[]){{0, 0, 1}});
	return (incomplete);
}

void	flush_buffer(int fd, t_buffer *buffer)
{
	write(fd, buffer->buffer, buffer->index);
	buffer->index = 0;
}

size_t	count_digits(size_t num)
{
	size_t	digits;

	digits = 0;
	while (num)
	{
		num /= 10;
		digits++;
	}
	return (digits);
}

void	print_instruction(t_lemin *info, t_array *program,
			t_buffer *buffer, size_t index)
{
	t_instruction	*instr;
	size_t			to_print;
	char			*format_string;
	char			*space;
	char			*name;

	name = NULL;
	space = NULL;
	instr = ((t_instruction*)program->ptr);
	if (instr[index].flusher)
		to_print = 1;
	else
	{
		format_string = "L%zu-%s%s";
		space = (index + 1 < program->length
			&& !instr[index + 1].flusher) ? " " : "";
		name = node_colony_data(&info->graph, instr[index].node_id)->name;
		to_print = 2 + ft_strlen(name) + ft_strlen(space)
			+ count_digits(instr[index].ant_id);
	}
	if (buffer->index + to_print > buffer->size)
		flush_buffer(1, buffer);
	if (instr[index].flusher)
		buffer->buffer[buffer->index++] = '\n';
	else
		buffer->index += ft_snprintf(buffer->buffer + buffer->index,
			buffer->size - buffer->index, format_string,
			instr[index].ant_id, name, space);
	index++;
}

void	print_program(t_lemin *info, t_array *program)
{
	t_buffer	buffer;
	size_t		index;

	index = 0;
	buffer.buffer = malloc(4096);
	buffer.index = 0;
	buffer.size = 4096;
	while (index < program->length)
		print_instruction(info, program, &buffer, index++);
	flush_buffer(1, &buffer);
}
