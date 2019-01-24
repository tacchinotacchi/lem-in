/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 23:02:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/24 13:20:38 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"

void	create_pq(t_pq *begin_pq, int elem_size)
{

	begin_pq->elem_size = elem_size;
	begin_pq->size = 0;
	begin_pq->used_size = 0;
	if (!(begin_pq->node = (void**)malloc(sizeof(void*) * size)))
		return (NULL);
	return;
}

int		add_pq(t_pq *pq, void *new_node, int(*cmp)(void*, void*))
{
	int		child;
	int		parent;

	child = pq->used_size;
	parent = (child - 1) / 2;

	if (pq->used_size == pq->size)
	{
		if (pq->used_size == 0)
			pq->used_size = 1;
		pq->size = pq->size * 2;
		if (!(pq->node = (void**)realloc(pq->node, sizeof(void*) * pq->size)))
			return (0);
	}
	pq->node[child] = new_node;
	while (child > 0 && cmp(pq->node[child], pq->node[parent]) < 0)
		swap_node_pq(pq, child, parent);
	pq->used_size++;
	return (1);
}

int		swap_node_pq(t_pq *pq, int child, int parent)
{
	void	**temp;

	if (!(temp = (void**)malloc(sizeof(void*))))
		return (0);
	ft_memcpy(temp, &(pq->node[child]), sizeof(void*));
	ft_memcpy(&(pq->node[child]), &(pq->node[parent]), sizeof(void*));
	ft_memcpy(&(pq->node[parent]), temp, sizeof(void*));
	free(temp);
	return (1);
}

int		pop_pq(t_pq *pq, void **pop, int(*cmp)(void*, void*))
{
	int		left_c;
	int		right_c;
	int		prior_c;
	int		parent;

	ft_memcpy(pop, &(pq->node[0]), sizeof(void*));
	ft_memset(&(pq->node[0]), 0, sizeof(void*));
	pq->used_size--;
	swap_node_pq(pq, 0, pq->used_size);
	left_c = 1;
	right_c = 2;
	while (left_c >= pq->used_size)
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
		left_c = (parent - 1) * 2;
		right_c = left_c + 1;
	}
	/*
	if (pq->used_size < (pq->size / 2))
	{
		pq->size /= 2;
		if (!(pq->node = (void**)realloc(pq->node, sizeof(void*) * pq->size)))
			return (0);
	}*/
	return (1);
}

void	destroy_pq(t_pq *pq)
{
	free(pq->node);
	free(pq);
}

int		check_empty_pq(t_pq *pq)
{
	return (pq->used_size == 0);
}
