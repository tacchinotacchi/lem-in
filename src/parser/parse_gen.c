/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 22:20:45 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/26 19:47:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "list.h"

int			store_ants(t_lemin *info, char *line, int index)
{
	info->ants = ft_atoi(line);
	return (index);
}

int			store_commands(t_lemin *info, char *line, int index)
{
	t_command	command;

	command.args = ft_strsplit(&line[2], ' ');
	if (!command.args)
		return (-1);
	list_append(&info->commands, list_new(&command.args, sizeof(t_command)));
	return (index);
}

int			store_comments(t_lemin *info, char *line, int index)
{
	list_add(&(info->comments), list_new(line, ft_strlen(line)));
	return (index);
}

static int	store_single_instruction(t_lemin *info, char *line)
{
	char			**array;
	t_tree			*name;
	t_name_node		node;
	t_instruction	instr;
	size_t			ant;

	array = ft_strsplit(line, '-');
	if (!array)
		return (FAIL);
	ant = ft_atoi(&array[0][1]);
	node.name = array[1];
	name = tree_search(info->name_tree, &node, compare_names);
	if (!name)
	{
		ft_splitdel(array);
		return (FAIL);
	}
	instr = (t_instruction){info->ants - ant + 1,
		LST_CONT(name, t_name_node).index, 0};
	list_append(&info->instructions, list_new(&instr, sizeof(t_instruction)));
	ft_splitdel(array);
	return (0);
}

int			store_instruction(t_lemin *info, char *line, int index)
{
	char			**array;
	t_instruction	flusher;
	size_t			instr;

	array = ft_strsplit(line, ' ');
	if (!array)
		return (FAIL);
	instr = 0;
	while (array[instr])
	{
		if (store_single_instruction(info, array[instr]) < 0)
		{
			ft_splitdel(array);
			return (FAIL);
		}
		instr++;
	}
	flusher = (t_instruction){0, 0, 1};
	list_append(&info->instructions, list_new(&flusher, sizeof(t_instruction)));
	ft_splitdel(array);
	return (index);
}
