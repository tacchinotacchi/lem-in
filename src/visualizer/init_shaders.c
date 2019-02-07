/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:59 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/06 16:59:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "visualizer.h"
#include "ft_printf.h"

static t_array	load_file(const char *filename)
{
	t_array	array;
	char	buffer[4096];
	int		err;
	int		fd;

	array_init(&array, sizeof(char[4096]));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (array);
	ft_bzero(buffer, 4096);
	while ((err = read(fd, buffer, 4096)) > 0)
	{
		array_push_back(&array, buffer);
		ft_bzero(buffer, 4096);
	}
	if (err < 0)
		array_clear(&array, NULL);
	close(fd);
	return (array);
}

static int	check_compile_error(GLuint *id, const char *message)
{
	GLint	info;
	char	*error;

	glGetShaderiv(*id, GL_COMPILE_STATUS, &info);
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

static int	check_link_error(GLuint *id, const char *message)
{
	GLint	info;
	char	*error;

	glGetProgramiv(*id, GL_LINK_STATUS, &info);
	if (info == GL_FALSE)
	{
		glGetProgramiv(*id, GL_INFO_LOG_LENGTH, &info);
		error = malloc(info);
		glGetProgramInfoLog(*id, info, NULL, error);
		ft_printf("%s: %s\n", message, error);
		free(error);
		return (-1);
	}
	return (0);
}

static int		init_any_shader(GLuint *id, GLenum shader_type, const char *filename)
{
	t_array	source;

	source = load_file(filename);
	if (source.length == 0)
		return (-1);
	*id = glCreateShader(shader_type);
	glShaderSource(*id,	1, (const char**)&source.ptr, NULL);
	array_clear(&source, NULL);
	glCompileShader(*id);
	if (check_compile_error(id, filename) < 0)
		return (-1);
	return (0);
}

static int		init_node_shader(t_renderer *renderer)
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
	if (check_link_error(&renderer->node_program, "Node shader linking:") < 0)
		return (-1);
	glDetachShader(renderer->node_program, vertex_shader);
	glDetachShader(renderer->node_program, geometry_shader);
	glDetachShader(renderer->node_program, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(frag_shader);
	return (0);
}

static int		init_edge_shader(t_renderer *renderer)
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
	renderer->edge_program = glCreateProgram();
	glAttachShader(renderer->edge_program, vertex_shader);
	glAttachShader(renderer->edge_program, geometry_shader);
	glAttachShader(renderer->edge_program, frag_shader);
	glLinkProgram(renderer->edge_program);
	if (check_link_error(&renderer->edge_program, "Edge shader linking:") < 0)
		return (-1);
	glDetachShader(renderer->edge_program, vertex_shader);
	glDetachShader(renderer->edge_program, geometry_shader);
	glDetachShader(renderer->edge_program, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(frag_shader);
	return (0);
}

static int		init_ant_shader(t_renderer *renderer)
{
	GLuint	vertex_shader;
	GLuint	geometry_shader;
	GLuint	frag_shader;


	if ((init_any_shader(&vertex_shader, GL_VERTEX_SHADER,
		"shaders/ant_vertex.glsl") < 0)
		|| (init_any_shader(&geometry_shader, GL_GEOMETRY_SHADER_EXT,
			"shaders/ant_geometry.glsl") < 0)
		|| (init_any_shader(&frag_shader, GL_FRAGMENT_SHADER,
			"shaders/ant_fragment.glsl") < 0))
		return (-1);
	renderer->ant_program = glCreateProgram();
	glAttachShader(renderer->ant_program, vertex_shader);
	glAttachShader(renderer->ant_program, geometry_shader);
	glAttachShader(renderer->ant_program, frag_shader);
	glLinkProgram(renderer->ant_program);
	if (check_link_error(&renderer->ant_program, "Ant shader linking:") < 0)
		return (-1);
	glDetachShader(renderer->ant_program, vertex_shader);
	glDetachShader(renderer->ant_program, geometry_shader);
	glDetachShader(renderer->ant_program, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(frag_shader);
	return (0);
}

int		init_shaders(t_renderer *renderer)
{
	if (init_node_shader(renderer) < 0
		|| init_edge_shader(renderer) < 0
		|| init_ant_shader(renderer) < 0)
		return (-1);
		/* TODO print error if file doesn't exist */
	return (0);
}
