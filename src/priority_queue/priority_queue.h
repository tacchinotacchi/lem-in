/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 11:59:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/01/22 23:46:30 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIORITY_QUEUE_H
# include <stdlib.h>
# include "libft.h"

typedef struct	s_pq
{
	void		**node;
	int			size;
	int			used_size;
}				t_pq;

t_pq			*create_pq(int size);
int				add_pq(t_pq *pq, void *new_node);
int				pop_pq(t_pq *pq, void *pop);
int				swap_node_pq(t_pq *pq, int child, int parent);
int				destroy_pq(t_pq *pq);
int				check_empty_pq(t_pq *pq);

#endif
