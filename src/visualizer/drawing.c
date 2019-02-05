/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/05 01:42:03 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "visualizer.h"

static void	draw_nodes(t_renderer *renderer)
{
	glUseProgram(renderer->node_program);
	glUniform1f(
		glGetUniformLocation(renderer->node_program, "node_scale"), 0.06f);
	glUniform1i(glGetUniformLocation(renderer->node_program, "note_tex"), 0);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "transform"),
		1, GL_TRUE, renderer->view.transform_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "rotation"),
		1, GL_TRUE, renderer->view.rotation_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "perspective"),
		1, GL_TRUE, renderer->view.perspective_mat);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->node_texture);
	glDrawArrays(GL_POINTS, 0, renderer->node_coords.length);
}

static void	draw_edges(t_renderer *renderer)
{
	glUseProgram(renderer->edge_program);
	glUniform1f(
		glGetUniformLocation(renderer->edge_program, "edge_scale"), 0.02f);
	glUniform1i(glGetUniformLocation(renderer->edge_texture, "edge_tex"), 0);
	glUniformMatrix4fv(glGetUniformLocation(renderer->edge_program, "transform"),
		1, GL_TRUE, renderer->view.transform_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->edge_program, "rotation"),
		1, GL_TRUE, renderer->view.rotation_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->edge_program, "perspective"),
		1, GL_TRUE, renderer->view.perspective_mat);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->edge_texture);
	glDrawElements(GL_LINES, renderer->edge_indices.length * 2,
		GL_UNSIGNED_INT, 0);
}

static void	draw_ants(t_renderer *renderer)
{
	glUseProgram(renderer->node_program);
	glUniform1f(
		glGetUniformLocation(renderer->node_program, "node_scale"), 0.035f);
	glUniform1i(glGetUniformLocation(renderer->edge_texture, "node_tex"), 0);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "transform"),
		1, GL_TRUE, renderer->view.transform_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "rotation"),
		1, GL_TRUE, renderer->view.rotation_mat);
	glUniformMatrix4fv(glGetUniformLocation(renderer->node_program, "perspective"),
		1, GL_TRUE, renderer->view.perspective_mat);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->ant_texture);
	glDrawArrays(GL_POINTS, 0, renderer->ant_coords.length);
}

void	draw_graph(t_renderer *renderer)
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(renderer->node_vao);
	glBufferData(GL_ARRAY_BUFFER, renderer->node_coords.length * sizeof(float[3]),
		renderer->node_coords.ptr, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		renderer->edge_indices.length * sizeof(GLuint[2]),
		renderer->edge_indices.ptr, GL_DYNAMIC_DRAW);
	draw_edges(renderer);
	draw_nodes(renderer);
	glBindVertexArray(renderer->ant_vao);
	glBufferData(GL_ARRAY_BUFFER, renderer->ant_coords.length * sizeof(float[3]),
		renderer->ant_coords.ptr, GL_DYNAMIC_DRAW);
	draw_ants(renderer);
}
