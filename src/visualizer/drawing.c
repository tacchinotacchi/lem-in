/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:45:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/03 11:28:41 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "adjacency_list.h"
#include "visualizer.h"

static float	transform_x(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_x_coord);
	result *= 1.8f/(float)(info->max_x_coord - info->min_x_coord);
	result = result - 1.8f/2.f;
	return (result);
}

static float	transform_y(t_lemin *info, int coord)
{
	float	result;

	result = (float)(coord - info->min_y_coord);
	result *= 1.8f/(float)(info->max_y_coord - info->min_y_coord);
	result = result - 1.8f/2.f;
	return (result);
}

void	generate_coords(t_lemin *info, t_visualizer *vis)
{
	size_t	id;

	vis->width = info->graph.nodes.length;
	vis->adj_matrix = ft_memalloc(vis->width * vis->width);
	id = 0;
	while (id < info->graph.nodes.length)
	{
		node_colony_data(&info->graph, id)->coords[0] = transform_x(info,
			node_colony_data(&info->graph, id)->x);
		node_colony_data(&info->graph, id)->coords[1] = transform_y(info,
			node_colony_data(&info->graph, id)->y);
		node_colony_data(&info->graph, id)->coords[2] = 1.f * sin(
			node_colony_data(&info->graph, id)->x);
		id++;
	}
	id = 0;
	while (id < info->graph.edges.length)
	{
		vis->adj_matrix[vis->width * edge_tail(&info->graph, id)
			+ edge_head(&info->graph, id)] = 1;
		id++;
	}
}

void	convert_input(t_lemin *info, t_renderer *renderer)
{
	size_t	id;

	id = 0;
	array_clear(&renderer->node_coords, NULL);
	while (id < info->graph.nodes.length)
	{
		array_push_back(&renderer->node_coords,
			node_colony_data(&info->graph, id)->coords);
		id++;
	}
	id = 0;
	array_clear(&renderer->edge_indices, NULL);
	while (id < info->graph.edges.length)
	{
		array_push_back(&renderer->edge_indices, (GLuint[2]){
			edge_tail(&info->graph, id),
			edge_head(&info->graph, id)
		});
		id += 2;
	}
}

void	draw_nodes(t_renderer *renderer)
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

void	draw_edges(t_renderer *renderer)
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

void	draw_graph(t_renderer *renderer)
{
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(renderer->node_vao);
	glBindBuffer(GL_ARRAY_BUFFER, renderer->node_buffer);
	glBufferData(GL_ARRAY_BUFFER, renderer->node_coords.length * sizeof(float[3]),
		renderer->node_coords.ptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->edge_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, renderer->edge_indices.length * sizeof(GLuint[2]),
		renderer->edge_indices.ptr, GL_DYNAMIC_DRAW);
	draw_edges(renderer);
	draw_nodes(renderer);
}
