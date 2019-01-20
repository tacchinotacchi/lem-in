/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacency_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 16:49:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/20 17:59:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "array.h"

typedef struct	s_colony_data
{
	char	*name;
	int		flags;
	int		x;
	int		y;
}				t_colony_data;

typedef	struct	s_node
{
	t_list	*edges;
	void	*data;
}				t_node;

typedef struct	s_edge
{
	size_t	tail;
	size_t	head;
	void	*data;
}				t_edge;

typedef struct	s_graph
{
	t_array nodes;
	t_array edges;
}				t_graph;

void	add_node(t_graph* graph, void *data);
void	add_edge(t_graph* graph, size_t tail, size_t head);
