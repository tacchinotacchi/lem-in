/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_node_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:09:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/06 15:04:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		store_node_data(t_lemin *info, t_colony_node_data *data)
{
	t_tree		*new_node_coord;
	t_tree		*new_node_name;
	t_name_node	name;

	add_node(&(info->graph), data, sizeof(t_colony_node_data));
	name.name = data->name;
	name.index = info->graph.nodes.length - 1;
	new_node_coord = node_create(&(data->coord), sizeof(uint64_t));
	new_node_name = node_create(&(name), sizeof(t_name_node));
	if (tree_insert(&(info->coord_tree), new_node_coord, compare_coords) == 0)
		return (FAIL);
	if (tree_insert(&(info->name_tree), new_node_name, compare_names) == 0)
		return (FAIL);
	if (data->x > info->max_x_coord)
		info->max_x_coord = data->x;
	if (data->x < info->min_x_coord)
		info->min_x_coord = data->x;
	if (data->y > info->max_y_coord)
		info->max_y_coord = data->y;
	if (data->y < info->min_y_coord)
		info->min_y_coord = data->y;
	return (1);
}

int		create_node_data(t_lemin *info, char *line, int index)
{
	t_colony_node_data	data;
	char				**split;

	if (!(split = ft_strsplit(line, ' ')))
		return (FAIL);
	init_colony_data(&data);
	if (!(data.name = ft_strdup(split[0])))
		return (FAIL);
	data.x = ft_atoi(split[1]);
	data.y = ft_atoi(split[2]);
	data.coord |= data.x;
	data.coord = data.coord << 32;
	data.coord |= data.y;
	data.ant = 0;
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
	return (store_node_data(info, &data) > 0 ? index : 0);
}
