/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 02:50:50 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "lem_in.h"
#include "visualizer.h"

static void		draw_nodes(t_lemin *info, t_renderer *renderer)
{
	glUseProgram(renderer->node_program);
	transform_matrices_set(renderer, renderer->node_program);
	glUniform1f(
		glGetUniformLocation(renderer->node_program, "node_scale"), 0.06f);
	glUniform1i(glGetUniformLocation(renderer->node_program, "note_tex"), 0);
	glUniform1i(glGetUniformLocation(renderer->node_program, "start_tex"), 1);
	glUniform1i(glGetUniformLocation(renderer->node_program, "end_tex"), 2);
	glUniform3fv(glGetUniformLocation(renderer->node_program, "start_coord"),
		1, node_colony_data(&info->graph, info->start)->coords);
	glUniform3fv(glGetUniformLocation(renderer->node_program, "end_coord"),
		1, node_colony_data(&info->graph, info->end)->coords);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->node_texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, renderer->start_texture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, renderer->end_texture);
	glDrawArrays(GL_POINTS, 0, renderer->node_coords.length);
}

static void		draw_edges(t_renderer *renderer)
{
	glUseProgram(renderer->edge_program);
	transform_matrices_set(renderer, renderer->edge_program);
	glUniform1f(
		glGetUniformLocation(renderer->edge_program, "edge_scale"), 0.02f);
	glUniform1i(glGetUniformLocation(renderer->edge_texture, "edge_tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->edge_texture);
	glDrawElements(GL_LINES, renderer->edge_indices.length * 2,
		GL_UNSIGNED_INT, 0);
}

static void		draw_ants(t_renderer *renderer)
{
	glUseProgram(renderer->ant_program);
	transform_matrices_set(renderer, renderer->ant_program);
	glUniform1f(glGetUniformLocation(renderer->ant_program, "ant_scale"),
		0.035f);
	glUniform1f(glGetUniformLocation(renderer->ant_program, "animation_time"),
		renderer->animation_time);
	glUniform1i(glGetUniformLocation(renderer->edge_texture, "ant_tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderer->ant_texture);
	glDrawElements(GL_LINES, renderer->ant_data.length * 2,
		GL_UNSIGNED_INT, 0);
}

void			draw_graph(t_lemin *info, t_renderer *renderer)
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(renderer->node_vao);
	glBufferData(GL_ARRAY_BUFFER,
		renderer->node_coords.length * sizeof(float[3]),
			renderer->node_coords.ptr, GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		renderer->edge_indices.length * sizeof(GLuint[2]),
			renderer->edge_indices.ptr, GL_DYNAMIC_DRAW);
	draw_edges(renderer);
	draw_nodes(info, renderer);
	glBindVertexArray(renderer->ant_vao);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		renderer->ant_data.length * sizeof(GLuint[2]),
			renderer->ant_data.ptr, GL_DYNAMIC_DRAW);
	draw_ants(renderer);
}
