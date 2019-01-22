/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:07:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 01:34:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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

void	get_comment(t_cmt **begin_list, char *line)
{
	t_cmt	*new_cmt;
	t_cmt	*temp;

	new_cmt = (t_cmt*)malloc(sizeof(t_cmt));
	new_cmt->cmt = ft_strdup(line);
	if (!temp)
	{
		*begin_list = new_cmt;
		return ;
	}
	while (temp)
	{
		if (!temp->next)
		{
			temp->next = new_cmt;
			return ;
		}
		temp = temp->next;
	}
}

void	get_start_data(t_lemin *info)
{
	char	*line;
	char	**split;

	while (get_next_line(0, &line) < 1 && line[0] == '#')
	{
		get_comment(&(info->cmt), line);
		free(line);
	}
	split = ft_strsplit(line, ' ');
	free(line);
	get_node_data(info, split, START);
}

void	get_end_data(t_lemin *info, t_data *data)
{
	char	*line;
	char	**split;

	while (get_next_line(0, &line) < 1 && line[0] == '#')
	{
		get_comment(&(info->cmt), line);
		free(line);
	}
	split = ft_strsplit(line, ' ');
	free(line);
	get_node_data(info, split, END);
}

void    get_node_data(t_lemin *info, char **split, int flags)
{
	t_data data;

	if (!split[0] || !split[1] || !split[2] || split[3] || split[0][0] == 'L' ||
			info->graph.edges.ptr || ft_strchr(split[0], '-'))
	{
		ft_splitdel(split);
		error(info);
	}
	data.name = ft_strdup(split[0]);
	data.x = ft_atoi(split[1]);
	data.y = ft_atoi(split[2]);
	data.flags = flags;
	ft_splitdel(split);
	add_node(&(info->graph), &data, sizeof(data));
}

ssize_t	search_nodes(t_array *nodes, char *node)
{
	ssize_t	index;

	index = 0;
	while (index * nodes->elem_size <= nodes->reserved)
	{
		if (!ft_strcmp(((t_data*)((t_node*)nodes->ptr)[index].data)->name, node))
			return (index);
		index++;
	}
	return (-1);
}

void	get_edge_data(t_lemin *info, char **split)
{
	ssize_t	tail;
	ssize_t	head;

	tail = 0;
	head = 0;

	if (!split[0] || !split[1] || split[2])
	{
		ft_splitdel(split);
		error(info);
	}
	tail = search_nodes(&(info->graph.nodes), split[0]);
	head = search_nodes(&(info->graph.nodes), split[1]);
	ft_splitdel(split);
	if (tail >= 0 && head >= 0)
		add_edge(&(info->graph), tail, head);
	else
		error(info);
}
