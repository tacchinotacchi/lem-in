/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:07:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/21 18:57:01 by jaelee           ###   ########.fr       */
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

void	get_start_data(t_lemin *info, t_data *data)
{
	char	*line;
	char	**split;

	while (get_next_line(0, &line) < 1)
	{
		if (line[0] == '#')
		{
			get_comment(&(info->cmt), line);
			free(line);
		}
		else
			break ;
	}
	split = ft_strsplit(line, ' ');
	free(line);
	get_node_data(info, data, split, START);
}

void	get_end_data(t_lemin *info, t_data *data)
{
	char	*line;
	char	**split;

	while (get_next_line(0, &line) < 1)
	{
		if (line[0] == '#')
		{
			get_comment(&(info->cmt), line);
			free(line);
		}
		else
			break ;
	}
	split = ft_strsplit(line, ' ');
	free(line);
	get_node_data(info, data, split, END);
}

void    get_node_data(t_lemin *info, t_data *data, char **split, int flags)
{
	if (!split[0] || !split[1] || !split[2] || split[3] || split[0][0] == 'L' ||
			info->graph.edges.ptr || ft_strchr(split[0], '-'))
	{
		ft_splitdel(split);
		error(info);
	}
	data = (t_data*)malloc(sizeof(t_data));
	data->name = ft_strdup(split[0]);
	data->x = ft_atoi(split[1]);
	data->y = ft_atoi(split[2]);
	data->flags = flags;
	ft_splitdel(split);
	add_node(&(info->graph), data); // NOT SURE!!
}

void	get_edge_data(t_lemin *info, char **split)
{
	size_t	tail;
	size_t	head;

	tail = 0;
	head = 0;
	tail = search_nodes(&(info->graph.nodes), split[0]);
	head = search_nodes(&(info->graph.nodes), split[1]);
	//TODO have to code search_nodes()
	add_edge(&(info->graph), tail, head);
}
