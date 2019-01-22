/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:49:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/22 12:46:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ADJACENCY_LIST_H
# define _ADJACENCY_LIST_H
# include "list.h"
# include "array.h"

typedef	struct	s_node
{
	t_list	*in_edges;
	t_list	*out_edges;
	void	*data;
}				t_node;

typedef struct	s_edge
{
	ssize_t	tail;
	ssize_t	head;
	void	*data;
}				t_edge;

typedef struct	s_graph
{
	t_array nodes;
	t_array edges;
}				t_graph;

void	add_node(t_graph* graph, void *data, size_t data_size);
void	add_edge(t_graph* graph, ssize_t tail, ssize_t head);

#endif
