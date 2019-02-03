/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:56:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 23:22:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser.h"
#include "adjacency_list.h"

void		init_colony_data(t_colony_node_data *data)
{
	data->flags = 0;
	data->name = NULL;
	data->flow_in_id = 0;
	data->flow_out_id = 0;
	data->x = 0;
	data->y = 0;
	data->coord = 0;
	data->ant = 0;
}

int		store_input(t_lemin *info, int index, char *line)
{
	int ret;

	ret = -1;
	if (index == l_ants)
		ret = store_ants(info, line, index);
	else if (index == l_start || index == l_end)
		return (index);
	else if (index == l_node || index == l_start_node || index == l_end_node)
		ret = store_node_data(info, line, index);
    else if (index == l_edge)
        ret = store_edge_data(info, line, index);
    else if (index == l_command)
		ret = store_commands(info, line, index);
	else if (index == l_comment)
		ret = store_comments(info, line, index);
	return (ret);
}

int 	  store_node_data(t_lemin *info, char *line, int index)
{
	t_colony_node_data	data;
	char			**split;

	if (!(split = ft_strsplit(line, ' ')))
	{
		ft_splitdel(split);
		return (FAIL);
	}
	init_colony_data(&data);
	if (!(data.name = ft_strdup(split[0])))
		return (FAIL);
	data.x = ft_atoi(split[1]);
	data.y = ft_atoi(split[2]);
	data.coord |= data.x;
	data.coord = data.coord << 32;
	data.coord |= data.y;
	if (index == l_start_node)
	{
		info->start = info->graph.nodes.length;
		data.flags |= START;
	}
	else if (index == l_end_node)
	{
		info->end = info->graph.nodes.length;
		data.flags |= END;
	}
	(t_name_node[]){{split[0], 0}}, compare_names);
	ft_splitdel(split);
	add_node(&(info->graph), &data, sizeof(data));
	if (tree_insert(&(info->coord_tree),
	node_create(&data.coord, sizeof(uint64_t)), compare_coords) == 0)
		return (FAIL);
	if (tree_insert(&(info->name_tree), node_create(&(t_name_node[]){{split[0],
	info->graph.nodes.length}}, sizeof(t_name_node)), compare_names) == 0)
		return (FAIL);
	if (data.x > info->max_x_coord)
		info->max_x_coord = data.x;
	if (data.x < info->min_x_coord)
		info->min_x_coord = data.x;
	if (data.y > info->max_y_coord)
		info->max_y_coord = data.y;
	if (data.y < info->min_y_coord)
		info->min_y_coord = data.y;
	return (index);
}


static t_edge_pair	get_edge_pair(t_lemin *info, char **split)
{
	t_tree		*node;
	size_t		first;
	size_t		second;

	node = tree_search(info->edge_tree,
		(t_name_node[]){{split[0], 0}}, compare_names);
	first = node ? ((t_name_node*)node->content)->index : 0;
	node = tree_search(info->edge_tree,
		(t_name_node[]){{split[1], 0}}, compare_names);
	second = node ? ((t_name_node*)node->content)->index : 0;
	if (first >= second)
		return ((t_edge_pair){first, second});
	return ((t_edge_pair){second, first});
}

int			compare_edge(const void *ptr1, const void *ptr2)
{
	const t_edge_pair	*pair1;
	const t_edge_pair	*pair2;

	pair1 = ptr1;
	pair2 = ptr2;
	if (pair1->major != pair2->major)
		return (pair1->major - pair2->major);
	return (pair1->minor - pair2->minor);
}

int	store_edge_data(t_lemin *info, char *line, int index)
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
	add_edge(&(info->graph), pair.minor, pair.major, sizeof(t_colony_edge_data));
	add_edge(&(info->graph), pair.major, pair.minor, sizeof(t_colony_edge_data));
	return (index);
}
