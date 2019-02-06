/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 23:26:04 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/06 14:17:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"

static void	update_color(t_lemin *info, t_command command)
{
	t_colony_node_data	*node_data;
	size_t				count;

	count = 0;
	while (command.args[count])
		count++;
	if (count == 5)
	{
		node_data = node_colony_data(&info->graph, ft_atoi(command.args[1]));
		node_data->color[0] = (float)ft_atoi(command.args[2]) / 255.f;
		node_data->color[1] = (float)ft_atoi(command.args[3]) / 255.f;
		node_data->color[2] = (float)ft_atoi(command.args[4]) / 255.f;
	}
}

static void	execute_command(t_lemin *info)
{
	t_command	command;
	t_list		*pop;

	pop = list_pop(&info->commands);
	if (pop)
	{
		command = LST_CONT(pop, t_command);
		if (command.args[0])
		{
			if (!ft_strcmp("color", command.args[0]))
				update_color(info, command);
			else
				ft_dprintf(2, "Command %s unknown\n", command.args[0]);
		}
		ft_splitdel(command.args);
	}
	free(pop);
}

void	handle_key(const SDL_Event *event, t_lemin *info, t_renderer *renderer)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	else if (event->key.keysym.sym == SDLK_w)
		renderer->view.velocity[2] = (event->key.type == SDL_KEYDOWN) ? 0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_s)
		renderer->view.velocity[2] = (event->key.type == SDL_KEYDOWN) ? -0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_a)
		renderer->view.velocity[0] = (event->key.type == SDL_KEYDOWN) ? 0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_d)
		renderer->view.velocity[0] = (event->key.type == SDL_KEYDOWN) ? -0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_n && event->key.type == SDL_KEYDOWN)
		execute_command(info);
}

void	handle_event(const SDL_Event *event, t_lemin *info,
			t_renderer *renderer)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		renderer->view.v_rotation -= 0.001f * event->motion.xrel;
		renderer->view.v_rotation = fmod(renderer->view.v_rotation, PI * 2.f);
		renderer->view.r_rotation += 0.001f * event->motion.yrel;
		if (renderer->view.r_rotation > PI / 2.f)
			renderer->view.r_rotation = PI / 2.f;
		else if (renderer->view.r_rotation < -PI / 2.f)
			renderer->view.r_rotation = -PI / 2.f;
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
		handle_key(event, info, renderer);
}

void	update_position(t_view *view)
{
	float	direction[3];

	ft_memcpy(direction, view->velocity, sizeof(float) * 3);
	rotate_vector(direction, -view->v_rotation, -view->r_rotation);
	view->position[0] += direction[0];
	view->position[1] += direction[1];
	view->position[2] += direction[2];
}
