/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:44:10 by jaelee            #+#    #+#             */
/*   Updated: 2019/02/07 19:45:08 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	matrix_add(float *dst, float *a, float *b)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i * 4 + j] = a[i * 4 + j] + b[i * 4 + j];
			j++;
		}
		i++;
	}
}

void	matrix_sub(float *dst, float *a, float *b)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dst[i * 4 + j] = a[i * 4 + j] - b[i * 4 + j];
			j++;
		}
		i++;
	}
}

void	matrix_mul(float *dst, float *a, float *b)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			dst[i * 4 + j] = 0;
			while (k < 4)
			{
				dst[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
				k++;
			}
			j++;
		}
		i++;
	}
}
