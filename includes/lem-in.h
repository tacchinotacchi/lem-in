/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 19:43:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 01:29:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# include "list.h"
# include "array.h"
# include "adjacency_list.h"
# include "libft.h"
# include <fcntl.h>
# define START 1
# define END 2
# define NODE 0

typedef struct	s_data
{
	char	*name;
	int		flags;
	int		x;
	int		y;
}				t_data;

typedef struct	s_cmt //TODO connection between comments and nodes required
{
	char			*cmt;
	struct s_cmt	*next;
}				t_cmt;

typedef struct 	s_lemin
{
	int		ants;
	t_cmt	*cmt;
	t_graph	graph;
}				t_lemin;

void	parse_input(t_lemin *info);
void	get_ants(t_lemin *info);
void	init_nodes_and_edges(t_graph *graph);
void	get_comment(t_cmt **begin_list, char *line);
void	get_start_data(t_lemin *info);
void	get_end_data(t_lemin *info);
void	get_node_data(t_lemin *info, char **split, int flags);
void	get_edge_data(t_lemin *info, char **split);
void	error(t_lemin *info);
ssize_t	search_nodes(t_array *nodes, char *node);
void	ft_splitdel(char **split);
#endif
