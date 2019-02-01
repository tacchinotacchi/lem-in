/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:59 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/01 11:46:39 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "visualizer.h"
#include "ft_printf.h"

static void	free_line(void *data)
{
	free(*(char**)data);
}

t_array		load_file(const char *filename)
{
	t_array	array;
	char	*line;
	int		err;
	int		fd;

	array_init(&array, sizeof(char*));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (array);
	while ((err = get_next_line(fd, &line) > 0))
	{
		if (line)
			array_push_back(&array, &line);
	}
	close(fd);
	return (array);
}

int		check_compile_error(GLuint *id, GLenum compilation_stage,
			const char *message)
{
	GLint	info;
	char	*error;

	glGetShaderiv(*id, compilation_stage, &info);
	if (info == GL_FALSE)
	{
		glGetShaderiv(*id, GL_INFO_LOG_LENGTH, &info);
		error = malloc(info);
		glGetShaderInfoLog(*id, info, NULL, error);
		ft_printf("%s: %s\n", message, error);
		free(error);
		return (-1);
	}
	return (0);
}

int		init_any_shader(GLuint *id, GLenum shader_type, const char *filename)
{
	t_array	source;

	source = load_file(filename);
	if (source.length == 0)
		return (-1);
	*id = glCreateShader(shader_type);
	glShaderSource(*id,	source.length, (const char**)source.ptr, NULL);
	array_clear(&source, free_line);
	glCompileShader(*id);
	if (check_compile_error(id, GL_COMPILE_STATUS, filename) < 0)
		return (-1);
	return (0);
}

int		init_node_shader(t_renderer *renderer)
{
	GLuint	vertex_shader;
	GLuint	geometry_shader;
	GLuint	frag_shader;


	if ((init_any_shader(&vertex_shader, GL_VERTEX_SHADER,
		"shaders/node_vertex.glsl") < 0)
		|| (init_any_shader(&geometry_shader, GL_GEOMETRY_SHADER_EXT,
			"shaders/node_geometry.glsl") < 0)
		|| (init_any_shader(&frag_shader, GL_FRAGMENT_SHADER,
			"shaders/node_fragment.glsl") < 0))
		return (-1);
	renderer->node_program = glCreateProgram();
	glAttachShader(renderer->node_program, vertex_shader);
	glAttachShader(renderer->node_program, geometry_shader);
	glAttachShader(renderer->node_program, frag_shader);
	glLinkProgram(renderer->node_program);
	if (check_compile_error(&renderer->node_program, GL_LINK_STATUS,
		"Shader linking:") < 0)
		return (-1);
	glDetachShader(renderer->node_program, vertex_shader);
	glDetachShader(renderer->node_program, geometry_shader);
	glDetachShader(renderer->node_program, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(frag_shader);
	return (0);
}

int		init_edge_shader(t_renderer *renderer)
{
	GLuint	vertex_shader;
	GLuint	geometry_shader;
	GLuint	frag_shader;


	if ((init_any_shader(&vertex_shader, GL_VERTEX_SHADER,
		"shaders/edge_vertex.glsl") < 0)
		|| (init_any_shader(&geometry_shader, GL_GEOMETRY_SHADER_EXT,
			"shaders/edge_geometry.glsl") < 0)
		|| (init_any_shader(&frag_shader, GL_FRAGMENT_SHADER,
			"shaders/edge_fragment.glsl") < 0))
		return (-1);
	renderer->node_program = glCreateProgram();
	glAttachShader(renderer->node_program, vertex_shader);
	glAttachShader(renderer->node_program, geometry_shader);
	glAttachShader(renderer->node_program, frag_shader);
	glLinkProgram(renderer->node_program);
	if (check_compile_error(&renderer->node_program, GL_LINK_STATUS,
		"Shader linking:") < 0)
		return (-1);
	glDetachShader(renderer->node_program, vertex_shader);
	glDetachShader(renderer->node_program, geometry_shader);
	glDetachShader(renderer->node_program, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(frag_shader);
	return (0);
}

int		init_shaders(t_renderer *renderer)
{
	if (init_node_shader(renderer) < 0
		|| init_edge_shader(renderer) < 0)
		return (-1);
	return (0);
}
