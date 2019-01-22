/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 15:21:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# include "list.h"
# include "adjacency_list.h"
# include "libft.h"
# define START 1
# define END 2
# define NODE 0

typedef struct	s_colony_data
{
	char	*name;
	int		flags;
	int		x;
	int		y;
	int		bfs_weight;
}				t_colony_data;

typedef struct	s_edge_data
{
	int		weight;
}				t_edge_data;

typedef struct 	s_lemin
{
	int		ants;
	t_list	*comments;
	t_graph	graph;
}				t_lemin;

void	parse_input(t_lemin *info);
void	get_ants(t_lemin *info);
void	init_nodes_and_edges(t_graph *graph);
void	get_start_data(t_lemin *info);
void	get_end_data(t_lemin *info);
void	get_node_data(t_lemin *info, char **split, int flags);
void	get_edge_data(t_lemin *info, char **split);
void	error(t_lemin *info);
ssize_t	search_nodes(t_array *nodes, char *node);
/* TODO review and move to libft */
void	ft_splitdel(char **split);
#endif
