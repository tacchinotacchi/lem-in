/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shaders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:49:59 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 16:18:15 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "visualizer.h"
#include "ft_printf.h"

static int		compile_shaders(GLuint *program, char *const *filenames,
					GLuint *shaders)
{
	const GLuint	shader_types[3] = {GL_VERTEX_SHADER,
		GL_GEOMETRY_SHADER,
		GL_FRAGMENT_SHADER};
	size_t			index;

	index = 0;
	while (index < 3)
	{
		if (filenames[index])
		{
			if (init_any_shader(&shaders[index],
				shader_types[index], filenames[index]) < 0)
				return (-1);
			glAttachShader(*program, shaders[index]);
		}
		index++;
	}
	return (0);
}

static int		init_shader(GLuint *program, char *const *filenames,
					const char *err_string)
{
	GLuint			shaders[3];
	size_t			index;

	*program = glCreateProgram();
	ft_bzero(shaders, sizeof(GLuint[3]));
	if (compile_shaders(program, filenames, shaders) < 0)
		return (-1);
	glLinkProgram(*program);
	if (check_link_error(program, err_string) < 0)
		return (-1);
	index = 0;
	while (index < 3)
	{
		glDetachShader(*program, shaders[index]);
		glDeleteShader(shaders[index++]);
	}
	return (0);
}

int				init_shaders(t_renderer *renderer)
{
	char	*filenames[3];

	filenames[0] = "shaders/node_vertex.glsl";
	filenames[1] = "shaders/node_geometry.glsl";
	filenames[2] = "shaders/node_fragment.glsl";
	if (init_shader(&renderer->node_program,
		filenames, "Node shader linking:") < 0)
		return (-1);
	filenames[0] = "shaders/edge_vertex.glsl";
	filenames[1] = "shaders/edge_geometry.glsl";
	filenames[2] = "shaders/edge_fragment.glsl";
	if (init_shader(&renderer->edge_program,
		filenames, "Edge shader linking:") < 0)
		return (-1);
	filenames[0] = "shaders/ant_vertex.glsl";
	filenames[1] = "shaders/ant_geometry.glsl";
	filenames[2] = "shaders/ant_fragment.glsl";
	if (init_shader(&renderer->ant_program,
		filenames, "Ant shader linking:") < 0)
		return (-1);
	return (0);
}
