/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:49:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/21 21:50:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "array.h"

typedef	struct	s_node
{
	t_list	*edges;
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

void	add_node(t_graph* graph, void *data);
void	add_edge(t_graph* graph, ssize_t tail, ssize_t head);
