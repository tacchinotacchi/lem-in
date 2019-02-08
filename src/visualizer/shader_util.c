/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 02:45:45 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 02:57:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	transform_matrices_set(t_renderer *renderer, GLuint program)
{
	glUniformMatrix4fv(glGetUniformLocation(program, "transform"),
		1, GL_TRUE, renderer->view.transform_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "rotation"),
		1, GL_TRUE, renderer->view.rotation_mat);
	glUniformMatrix4fv(glGetUniformLocation(program, "perspective"),
		1, GL_TRUE, renderer->view.perspective_mat);
}
