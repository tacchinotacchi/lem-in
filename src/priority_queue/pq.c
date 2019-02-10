/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:16:59 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/10 18:20:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priority_queue.h"

void	pq_init(t_pq *pq, size_t data_size)
{
	array_init(&pq->nodes, sizeof(void*));
	pq->data_size = data_size;
}

static void	free_container(void *ptr)
{
	void	**container;

	container = ptr;
	free(*container);
}

void	pq_destroy(t_pq *pq)
{
	/* TODO ft_free_stub? */
	array_clear(&pq->nodes, free_container);
	pq->data_size = 0;
}

void	pq_add(t_pq *pq, const void *data, t_comparison cmp)
{
	void	*container;

	container = malloc(pq->data_size);
	if (!container)
		return ;
	ft_memcpy(container, data, pq->data_size);
	array_push_back(&pq->nodes, &container);
	pq_raise(pq, pq->nodes.length - 1, cmp);
}

void	*pq_pop(t_pq *pq, t_comparison cmp)
{
	void	*popped;

	if (pq->nodes.length == 0)
		return (NULL);
	pq_swap(pq, 0, pq->nodes.length - 1);
	popped = ARRAY_PTR(pq->nodes, void*)[pq->nodes.length - 1];
	array_pop_back(&pq->nodes, NULL);
	pq_sink(pq, cmp);
	return (popped);
}

int		pq_empty(t_pq *pq)
{
	return (pq->nodes.length == 0);
}
