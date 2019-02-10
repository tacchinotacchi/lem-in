/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq_rebalance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 18:08:20 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/10 18:18:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"

static int	do_comparison(t_pq *pq, size_t node1,
				size_t node2, t_comparison cmp)
{
	return(cmp(ARRAY_PTR(pq->nodes, void*)[node1],
		ARRAY_PTR(pq->nodes, void*)[node2]));
}

void	pq_swap(t_pq *pq, size_t node1, size_t node2)
{
	void	*tmp;

	tmp = ARRAY_PTR(pq->nodes, void*)[node1];
	ARRAY_PTR(pq->nodes, void*)[node1] = ARRAY_PTR(pq->nodes, void*)[node2];
	ARRAY_PTR(pq->nodes, void*)[node2] = tmp;
}

void	pq_raise(t_pq *pq, size_t node, t_comparison cmp)
{
	size_t	parent;
	int		last_comparison;
	
	if (node == 0 || pq->nodes.length <= 1)
		return ;
	parent = (node - 1) / 2;
	last_comparison = do_comparison(pq, node, parent, cmp);
	while (last_comparison > 0)
	{
		pq_swap(pq, node, parent);
		node = parent;
		if (node == 0)
			break;
		parent = (node - 1) / 2;
		last_comparison = do_comparison(pq, node, parent, cmp);
	}
}

static size_t	sink_choose_child(t_pq *pq, size_t node, t_comparison cmp)
{
	size_t	left_child;
	size_t	right_child;

	left_child = node * 2 + 1;
	right_child = left_child + 1;
	if (right_child < pq->nodes.length)
	{
		if (do_comparison(pq, left_child, right_child, cmp) >= 0)
			return (left_child);
		else
			return (right_child);
	}
	else if (left_child < pq->nodes.length)
		return (left_child);
	return (pq->nodes.length);
}

void	pq_sink(t_pq *pq, t_comparison cmp)
{
	size_t	node;
	size_t	child;

	node = 0;
	child = sink_choose_child(pq, node, cmp);
	while (child < pq->nodes.length)
	{
		if (cmp(ARRAY_PTR(pq->nodes, void*)[node],
			ARRAY_PTR(pq->nodes, void*)[child]) < 0)
			pq_swap(pq, node, child);
		else
			break ;
		node = child;
		child = sink_choose_child(pq, node, cmp);
	}
}
