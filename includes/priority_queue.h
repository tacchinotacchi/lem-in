/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:59:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/07 22:54:44 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIORITY_QUEUE_H
# define PRIORITY_QUEUE_H
# include <stdlib.h>
# include "libft.h"

typedef struct	s_pq_node
{
	void	*node;
	int		index;
}				t_pq_node;

typedef struct	s_pq
{
	void	**node;
	int		size;
	int		elem_size;
	int		used_size;
}				t_pq;

void			pq_init(t_pq *begin_pq, int elem_size);
int				pq_add(t_pq *pq, void *new_node, int (*cmp)(void*, void*));
void			*pq_pop(t_pq *pq, int (*cmp)(void*, void*));
void			pq_swap_node(t_pq *pq, int node1, int node2);
void			pq_destroy(t_pq *pq);
int				pq_empty(t_pq *pq);
void			*pq_resize(void *pq, size_t old_size, size_t new_size);

#endif
