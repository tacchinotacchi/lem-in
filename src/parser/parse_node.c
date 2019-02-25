/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:09:21 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/25 22:09:38 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	data->own_id = 0;
}

static void	update_coordinates(t_lemin *info, t_colony_node_data *data)
{
	if (data->x > info->max_x_coord)
		info->max_x_coord = data->x;
	if (data->x < info->min_x_coord)
		info->min_x_coord = data->x;
	if (data->y > info->max_y_coord)
		info->max_y_coord = data->y;
	if (data->y < info->min_y_coord)
		info->min_y_coord = data->y;
}

int			store_node_data(t_lemin *info, t_colony_node_data *data)
{
	t_tree		*new_node_coord;
	t_tree		*new_node_name;
	t_name_node	name;

	name.name = ft_strdup(data->name);
	name.index = info->graph.nodes.length;
	new_node_coord = node_create(&(data->coord), sizeof(uint64_t));
	if (tree_insert(&(info->coord_tree), new_node_coord, compare_coords) == 0)
	{
		free(name.name);
		free(data->name);
		tree_clear(&new_node_coord, free_stub);
		return (FAIL);
	}
	new_node_name = node_create(&(name), sizeof(t_name_node));
	if (tree_insert(&(info->name_tree), new_node_name, compare_names) == 0)
	{
		free(data->name);
		tree_clear(&new_node_name, free_t_name_node);
		return (FAIL);
	}
	data->own_id = info->graph.nodes.length;
	add_node(&(info->graph), data, sizeof(t_colony_node_data));
	update_coordinates(info, data);
	return (1);
}

static void	node_data_flag_update(t_lemin *info, t_colony_node_data *data,
			int index)
{
	if (index == l_start_node)
	{
		info->start = info->graph.nodes.length;
		data->flags |= START;
	}
	else if (index == l_end_node)
	{
		info->end = info->graph.nodes.length;
		data->flags |= END;
	}
}

int			create_node_data(t_lemin *info, char *line, int index)
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
	if (index == l_start_node || index == l_end_node)
		node_data_flag_update(info, &data, index);
	ft_splitdel(split);
	return (store_node_data(info, &data) > 0 ? index : -1);
}
