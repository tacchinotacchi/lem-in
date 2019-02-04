/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 04:03:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/04 04:06:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	flags_turn_on(int *field, int bits)
{
	*field |= bits;
}

void	flags_turn_off(int *field, int bits)
{
	*field &= ~bits;
}
