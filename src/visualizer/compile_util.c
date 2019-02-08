/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:44:02 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 16:19:25 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "array.h"
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
	{
		ft_dprintf(2, "Failed to open file: %s\n", filename);
		return (array);
	}
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

static int		check_compile_error(GLuint *id, const char *message)
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

int				check_link_error(GLuint *id, const char *message)
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

int				init_any_shader(GLuint *id, GLenum shader_type,
					const char *filename)
{
	t_array	source;

	source = load_file(filename);
	if (source.length == 0)
		return (-1);
	*id = glCreateShader(shader_type);
	glShaderSource(*id, 1, (const char**)&source.ptr, NULL);
	array_clear(&source, NULL);
	glCompileShader(*id);
	if (check_compile_error(id, filename) < 0)
		return (-2);
	return (0);
}
