/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:56:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/03 22:24:45 by aamadori         ###   ########.fr       */
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

static uint64_t cmp_coord(const void *data1, const void *data2)
{
	return (*(uint64_t*)data1 - *(uint64_t*)data2);
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
	ft_splitdel(split);
	add_node(&(info->graph), &data, sizeof(data));
	tree_insert(&(info->coord_tree), node_create(&data.coord, sizeof(uint64_t)), cmp_coord);
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

int	search_nodes(t_array *nodes, char *node)
{
	int	index;

	index = 0;
	while (index < (ssize_t)nodes->length)
	{
		if (!ft_strcmp(((t_colony_node_data*)
			((t_node*)nodes->ptr)[index].data)->name, node))
			return (index);
		index++;
	}
	return (-1);
}

int	store_edge_data(t_lemin *info, char *line, int index)
{
	int		tail;
	int		head;
	char	**split;

	tail = 0;
	head = 0;
	if (!(split = ft_strsplit(line, '-')))
	{
		ft_splitdel(split);
		return (FAIL);
	}
	tail = search_nodes(&(info->graph.nodes), split[0]);
	head = search_nodes(&(info->graph.nodes), split[1]);
	ft_splitdel(split);
	if (tail > -1 && head > -1)
	{
		add_edge(&(info->graph), tail, head, sizeof(t_colony_edge_data));
		add_edge(&(info->graph), head, tail, sizeof(t_colony_edge_data));
		return (index);
	}
	return (FAIL);
}
