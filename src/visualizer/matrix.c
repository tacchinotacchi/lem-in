/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:42:42 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 00:58:03 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include <math.h>

void	rotate_vector(float *v, float v_rotation, float r_rotation)
{
	float	temp[3];

	ft_memcpy(temp, v, sizeof(float) * 3);
	v[1] = temp[1] * cos(r_rotation) - temp[2] * sin(r_rotation);
	v[2] = temp[1] * sin(r_rotation) + temp[2] * cos(r_rotation);
	ft_memcpy(temp, v, sizeof(float) * 3);
	v[0] = temp[0] * cos(v_rotation) - temp[2] * sin(v_rotation);
	v[2] = temp[0] * sin(v_rotation) + temp[2] * cos(v_rotation);
}

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

void	matrix_perspective(float *mat, float near_clip, float far_clip,
			float fov)
{
	float	near_width;

	near_width = near_clip * tan(fov / 2.f);
	ft_bzero(mat, sizeof(float) * 16);
	mat[0 * 4 + 0] = near_clip / near_width;
	mat[1 * 4 + 1] = near_clip / near_width;
	mat[2 * 4 + 2] = -(far_clip + near_clip) / (far_clip - near_clip);
	mat[2 * 4 + 3] = -2.f * (far_clip * near_clip) / (far_clip - near_clip);
	mat[3 * 4 + 2] = -1.f;
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
	rotation[0 * 4 + 0] = cos(y_axis);
	rotation[0 * 4 + 2] = -sin(y_axis);
	rotation[2 * 4 + 0] = sin(y_axis);
	rotation[2 * 4 + 2] = cos(y_axis);
	matrix_mul(inter, rotation, mat);
	matrix_identity(rotation);
	rotation[1 * 4 + 1] = cos(x_axis);
	rotation[1 * 4 + 2] = -sin(x_axis);
	rotation[2 * 4 + 1] = sin(x_axis);
	rotation[2 * 4 + 2] = cos(x_axis);
	matrix_mul(mat, rotation, inter);
}
