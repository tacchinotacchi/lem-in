/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 18:56:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/21 21:44:30 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	while (get_next_line(0, &line) < 1 && line[0] == '#')
			get_comment(&(info->cmt), line);
	if (line == NULL)
		error(info);
	info->ants = ft_atoi(line);
	if (info->ants <= 0)
		error(info);
}

void	parse_input(t_lemin *info)
{
	char	*line;
	t_data	*data;

	init_nodes_and_edges(&(info->graph));
	get_ants(info);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strstr(line, "##start\n") && ft_strlen(line) == 8)
			get_start_data(info, data);
		else if (ft_strstr(line, "##end\n") && ft_strlen(line) == 6)
			get_end_data(info, data);
		else if (line[0] == '#')
			get_comment(&(info->cmt), line);
		else if (ft_strchr(line, ' '))
			get_node_data(info, data, ft_strsplit(line, ' '), NODE);
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

	parse_input(&info);

	return (0);
}
