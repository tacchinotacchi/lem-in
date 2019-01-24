/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 23:02:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/24 18:41:39 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"

void	create_pq(t_pq *begin_pq, int elem_size)
{
	begin_pq->elem_size = elem_size;
	begin_pq->size = 0;
	begin_pq->used_size = 0;
	begin_pq->node = NULL;
	/*if (!(begin_pq->node = (void**)malloc(begin_pq->elem_size * begin_pq->size)))
		return (0);*/
}

int		add_pq(t_pq *pq, void *new_node, int(*cmp)(void*, void*))
{
	int		child;
	int		parent;

	child = pq->used_size;
	parent = (child - 1) / 2;
	if (pq->used_size == pq->size)
	{
		pq->size = (pq->size + 1) * 2 - 1;
		if (!(pq->node = (void**)realloc(pq->node, sizeof(void*) * pq->size)))
			return (-1);
	}
	pq->node[child] = malloc(pq->elem_size);
	ft_memcpy(pq->node[child], new_node, pq->elem_size);
	while (child > 0 && cmp(pq->node[child], pq->node[parent]) < 0)
	{
		if (cmp(pq->node[child], pq->node[parent]) < 0)
		{
			swap_node_pq(pq, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
	}
	pq->used_size++;
	return (0);
}

void	swap_node_pq(t_pq *pq, int child, int parent)
{
	void	*temp;

	temp = pq->node[child];
	pq->node[child] = pq->node[parent];
	pq->node[parent] = temp;
}

void	*pop_pq(t_pq *pq, int(*cmp)(void*, void*))
{
	int		left_c;
	int		right_c;
	int		prior_c;
	int		parent;
	void	*pop;

	pop = pq->node[0];
	pq->node[0] = NULL;
	pq->used_size--;
	swap_node_pq(pq, 0, pq->used_size);
	left_c = 1;
	right_c = 2;
	parent = 0;
	while (left_c < pq->used_size)
	{
		if (right_c >= pq->used_size)
			prior_c = left_c;
		else
		{
			if (cmp(pq->node[left_c], pq->node[right_c]) < 0)
				prior_c = left_c;
			else
				prior_c = right_c;
		}
		if (cmp(pq->node[prior_c], pq->node[parent]) < 0)
		{
			swap_node_pq(pq, prior_c, parent);
			parent = prior_c;
		}
		else
			break ;
		left_c = (parent * 2) + 1;
		right_c = left_c + 1;
	}
/*	
	if (pq->used_size < (pq->size / 2))
	{
		pq->size /= 2;
		if (!(pq->node = (void**)realloc(pq->node, pq->elem_size * pq->size)))
			return (0);
	} Shrink func needs to be implemented */
	return (pop);
}

void	destroy_pq(t_pq *pq)
{
	int index;

	index = 0;
	while (index < pq->used_size)
	{
		free(pq->node[index]);
		index++;
	}
	free(pq->node);
	pq->node = NULL;
	pq->size = 0;
	pq->elem_size = 0;
	pq->used_size = 0;
}

int		check_empty_pq(t_pq *pq)
{
	return (pq->used_size == 0);
}
