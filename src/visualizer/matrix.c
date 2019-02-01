/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:42:42 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/01 21:16:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	matrix_identity(float *mat)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
			j++;
		}
		i++;
	}
}

void	matrix_add_movement(float *mat, float *direction)
{
	mat[0 * 4 + 3] += direction[0];
	mat[1 * 4 + 3] += direction[1];
	mat[2 * 4 + 3] += direction[2];
}

void	matrix_add_rotation(float *mat, float y_axis, float x_axis)
{
	float	inter[16];
	float	rotation[16];

	matrix_identity(inter);
	matrix_identity(rotation);
	rotation[0 * 4 + 0] = ft_cos(y_axis);
	rotation[0 * 4 + 2] = -ft_sin(y_axis);
	rotation[2 * 4 + 0] = ft_sin(y_axis);
	rotation[2 * 4 + 2] = ft_cos(y_axis);
	matrix_mul(inter, mat, rotation);
	matrix_identity(rotation);
	rotation[1 * 4 + 1] = ft_cos(x_axis);
	rotation[1 * 4 + 2] = -ft_sin(x_axis);
	rotation[2 * 4 + 1] = ft_sin(x_axis);
	rotation[2 * 4 + 2] = ft_cos(x_axis);
	matrix_mul(mat, inter, rotation);
}

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
