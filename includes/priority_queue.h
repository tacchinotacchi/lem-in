/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:59:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/10 18:10:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIORITY_QUEUE_H
# define PRIORITY_QUEUE_H
# include <stdlib.h>
# include "array.h"
# include "libft.h"

typedef struct	s_pq
{
	t_array	nodes;
	size_t	data_size;
}				t_pq;

void			pq_init(t_pq *pq, size_t data_size);
void			pq_add(t_pq *pq, const void *data, t_comparison cmp);
void			*pq_pop(t_pq *pq, t_comparison cmp);
void			pq_swap(t_pq *pq, size_t node1, size_t node2);
void			pq_raise(t_pq *pq, size_t node, t_comparison cmp);
void			pq_sink(t_pq *pq, t_comparison cmp);
void			pq_destroy(t_pq *pq);
int				pq_empty(t_pq *pq);

#endif
