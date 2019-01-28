/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 18:56:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/28 14:30:36 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser.h"
#include "adjacency_list.h"

void		init_colony_data(t_colony_data *data)
{
	data->flags = 0;
	data->name = NULL;
	data->flow_in_id = 0;
	data->flow_out_id = 0;
	data->x = 0;
	data->y = 0;
}

void	ft_splitdel(char **split)
{
	int index;

	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}

ssize_t		store_input(t_lemin *info, ssize_t index, char *line)
{
	ssize_t ret;

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

ssize_t 	  store_node_data(t_lemin *info, char *line, ssize_t index)
{
	t_colony_data	data;
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
	if (index == l_start_node)
		data.flags |= START;
	else if (index == l_end_node)
		data.flags |= END;
	ft_splitdel(split);
	add_node(&(info->graph), &data, sizeof(data));
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

ssize_t	search_nodes(t_array *nodes, char *node)
{
	ssize_t	index;

	index = 0;
	while (index < (ssize_t)nodes->length)
	{
		if (!ft_strcmp(((t_colony_data*)
			((t_node*)nodes->ptr)[index].data)->name, node))
			return (index);
		index++;
	}
	return (-1);
}

ssize_t	store_edge_data(t_lemin *info, char *line, ssize_t index)
{
	ssize_t	tail;
	ssize_t	head;
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
		add_edge(&(info->graph), tail, head, sizeof(void));
		add_edge(&(info->graph), head, tail, sizeof(void));
		return (index);
	}
	return (FAIL);
}
