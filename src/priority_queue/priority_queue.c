/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 23:02:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 23:44:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

t_pq	*create_pq(int size)
{
	t_pq	*begin_pq;

	if (!(begin_pq = (t_pq*)malloc(sizeof(t_pq))))
		return (NULL);
	begin_pq->size = size;
	begin_pq->used_size = 0;
	if (!(begin_pq->node = (void**)malloc(sizeof(void*) * size)))
		return (NULL);
	return (begin_pq);
}

int		add_pq(t_pq *pq, void *new_node) //TODO add cmp function ptr
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
		if (!(pq->node = (void**)realloc(sizeof(void*) * pq->size)))
			return (0); //TODO realloc needs to be FUCKIN coded
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
	ft_memcpy(temp, &(t_pq->node[child]), sizeof(void*));
	ft_memcpy(&(t_pq->node[child]), &(t_pq->node[parent]), sizeof(void*));
	ft_memcpy(&(t_pq->node[parent]), temp, sizeof(void*));
	free(temp); //TODO probably optimize by making memcpy to copy 2 bytes at once?
	return (1);
}

//TODO int cmp(pq->node[child], pq->node[parent])
//return n < 0 - if child is smaller than parent
//return n > 0 - if child is bigger than parent
int		pop_pq(t_pq *pq, void **pop)
{
	int		left_c;
	int		right_c;
	int		prior_c;
	int		parent;

	ft_memcpy(pop, &(t_pq->node[0]), sizeof(void*));
	ft_memset(&(t_pq->node[0]), 0, sizeof(void*));
	pq->used_size--;
	swap_node_pq(pq, 0, used_size);
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
	if (pq->used_size < (pq->size / 2))
	{
		pq->size /= 2;
		if (!(pq->node = (void**)realloc(sizeof(void*) * pq->size)))
			return (0);
	}
	return (1);
}

void	destroy_pq(t_pq *pq)
{
	free(pq->node);
	free(pq);
}

int		check_empty_pq(t_pq *pq)
{
	return (t_pq->used_size == 0);
}

//TODO add priority = int cmp(void *data1, void *data2)

int		main()
{
	int 		i;
	int 		nbr_nodes;
	t_pq		*pq;
	t_node_pq	*popped;
	t_node_pq	node[7] = {
		{"data", 3},
		{"queue", 7},
		{"fuck", 1},
	pq = create_pq(4);
	
