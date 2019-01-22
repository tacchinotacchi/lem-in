/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:56:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 21:20:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lem-in.h"

void	init_nodes_and_edges(t_graph *graph)
{
	graph->nodes.ptr = NULL;
	graph->nodes.elem_size = sizeof(t_node);
	graph->nodes.length = 0;
	graph->nodes.reserved = 0;

	graph->edges.ptr = NULL;
	graph->edges.elem_size = sizeof(t_edge);
	graph->edges.length = 0;
	graph->edges.reserved = 0;
}

void	get_ants(t_lemin *info)
{
	char	*line;

	/* TODO this adds repeating ##start and ##end lines as comments */
	while (get_next_line(0, &line) < 1 && line[0] == '#')
			list_add(&info->comments, list_new(line, ft_strlen(line) + 1));
	if (line == NULL)
		error(info);
	/* TODO check if the line is comprised only of numbers */
	info->ants = ft_atoi(line);
	if (info->ants <= 0)
		error(info);
}

void	parse_input(t_lemin *info)
{
	char	*line;

	init_nodes_and_edges(&(info->graph));
	get_ants(info);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcmp(line, "##start") == 0)
			get_start_data(info);
		else if (ft_strcmp(line, "##start") == 0)
			get_end_data(info);
		/* TODO this adds repeating ##start and ##end lines as comments */
		else if (line[0] == '#')
			list_add(&info->comments, list_new(line, ft_strlen(line) + 1));
		else if (ft_strchr(line, ' '))
			get_node_data(info, ft_strsplit(line, ' '), NODE);
		else if (ft_strchr(line, '-'))
			get_edge_data(info, ft_strsplit(line, '-'));
		else
		{
			free(line);
			error(info);
		}
		free(line);
	}
}

int		main(void)
{
	t_lemin	info;

	ft_bzero(&info, sizeof(t_lemin));
	info.max_x_coord = INT_MIN;
	info.min_x_coord = INT_MAX;
	info.max_y_coord = INT_MIN;
	info.min_y_coord = INT_MAX;
	parse_input(&info);
	return (0);
}
