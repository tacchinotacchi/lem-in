/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:56:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/07 13:42:50 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser.h"
#include "adjacency_list.h"

int					store_input(t_lemin *info, int index, char *line)
{
	int ret;

	ret = -1;
	if (index == l_ants)
		ret = store_ants(info, line, index);
	else if (index == l_start || index == l_end)
		return (index);
	else if (index == l_node || index == l_start_node || index == l_end_node)
		ret = create_node_data(info, line, index);
	else if (index == l_edge)
		ret = store_edge_data(info, line, index);
	else if (index == l_command)
		ret = store_commands(info, line, index);
	else if (index == l_comment)
		ret = store_comments(info, line, index);
	else if (index == l_instruction)
		ret = store_instruction(info, line, index);
	return (ret);
}

static t_edge_pair	get_edge_pair(t_lemin *info, char **split)
{
	t_tree		*node;
	size_t		first;
	size_t		second;
	t_name_node name1;
	t_name_node	name2;

	name1.name = split[0];
	name1.index = 0;
	name2.name = split[1];
	name2.index = 0;
	if (!ft_strcmp(split[0], split[1]))
		return ((t_edge_pair){0, 0});
	node = tree_search(info->name_tree, &name1, compare_names);
	first = node ? ((t_name_node*)node->content)->index : 0;
	node = tree_search(info->name_tree, &name2, compare_names);
	second = node ? ((t_name_node*)node->content)->index : 0;
	if (first >= second)
		return ((t_edge_pair){first, second});
	return ((t_edge_pair){second, first});
}

int					store_edge_data(t_lemin *info, char *line, int index)
{
	t_edge_pair	pair;
	char		**split;

	if (!(split = ft_strsplit(line, '-')))
	{
		ft_splitdel(split);
		return (FAIL);
	}
	pair = get_edge_pair(info, split);
	if (pair.minor == pair.major
		|| !tree_insert(&info->edge_tree,
			node_create(&pair, sizeof(pair)), compare_edge))
	{
		ft_splitdel(split);
		return (FAIL);
	}
	add_edge(&(info->graph), pair.minor, pair.major,
		sizeof(t_colony_edge_data));
	add_edge(&(info->graph), pair.major, pair.minor,
		sizeof(t_colony_edge_data));
	return (index);
}

static int			store_single_instruction(t_lemin *info, char *line)
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
	instr = (t_instruction){ant, LST_CONT(name, t_name_node).index, 0};
	list_append(&info->instructions, list_new(&instr, sizeof(t_instruction)));
	ft_splitdel(array);
	return (0);
}

int					store_instruction(t_lemin *info, char *line, int index)
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
