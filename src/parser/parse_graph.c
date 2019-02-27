/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:56:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/27 15:54:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
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
	first = node ? ((t_name_node*)node->content)->index
		: info->graph.nodes.length;
	node = tree_search(info->name_tree, &name2, compare_names);
	second = node ? ((t_name_node*)node->content)->index
		: info->graph.nodes.length;
	if (first >= second)
		return ((t_edge_pair){first, second});
	return ((t_edge_pair){second, first});
}

static int			pair_valid(t_lemin *info, t_edge_pair pair)
{
	return (pair.minor != pair.major
		&& pair.minor != info->graph.nodes.length
		&& pair.major != info->graph.nodes.length);
}

int					store_edge_data(t_lemin *info, char *line, int index)
{
	t_edge_pair	pair;
	t_tree		*new_node;
	char		**split;

	if (!(split = ft_strsplit(line, '-')))
		return (FAIL);
	pair = get_edge_pair(info, split);
	new_node = NULL;
	if (pair_valid(info, pair))
	{
		new_node = node_create(&pair, sizeof(pair));
		if (tree_insert(&info->edge_tree, new_node, compare_edge) == 0)
			tree_clear(&new_node, free_stub);
	}
	ft_splitdel(split);
	if (new_node)
	{
		add_edge(&(info->graph), pair.minor, pair.major,
			sizeof(t_colony_edge_data));
		add_edge(&(info->graph), pair.major, pair.minor,
			sizeof(t_colony_edge_data));
	}
	return (pair_valid(info, pair) ? index : FAIL_SOFT);
}
