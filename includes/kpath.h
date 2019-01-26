/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kpath.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:38:17 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/26 18:41:36 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _K_PATH_H
# define _K_PATH_H
# include "adjacency_list.h"
# include "array.h"
# include "priority_queue.h"

struct s_lemin;

typedef struct	s_path_data
{
	size_t	pseudotree_id;
	size_t	creation_time;
	size_t	graph_id;
	size_t	cost;
}				t_path_data;

typedef struct	s_path_graph
{
	size_t	time_frame;
	t_graph	*graph;
}				t_path_graph;

typedef struct	s_path
{
	t_list	*nodes;
	t_graph *path_tree;
	size_t 	dev_node;
	ssize_t	rank;
}				t_path;

size_t	add_node_pseudotree(t_path_graph *snapshot, size_t parent, size_t graph_id);
t_path	next_acceptable_path(struct s_lemin *input,
			t_path_graph *snapshot, t_pq *candidates);
int		pseudotree_cmp(void *data1, void *data2);
void	node_reserve(struct s_lemin *input, t_path_data *path_node);
int		mark_node(struct s_lemin *input, t_path_graph *snapshot, size_t path_id);
void	unmark(struct s_lemin *input, t_path_graph *snapshot, size_t path_id);
int		explore_sidetracks(struct s_lemin *input, t_path_graph *snapshot,
			t_pq *candidates, size_t path_id);
size_t	walk_up_tree(struct s_lemin *input, t_path_graph *snapshot, t_path *path,
			size_t after_dev);
void	prune_path(struct s_lemin *input, t_path_graph *snapshot, t_path *path,
			size_t after_dev);
t_path_data	*node_path_data(const t_graph *graph, size_t index);

#endif
