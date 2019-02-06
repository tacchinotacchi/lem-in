/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 23:26:04 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/06 16:08:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"

static ssize_t	instruction_is_valid(t_lemin *info, t_instruction instr)
{
	t_colony_node_data	*node_data;
	t_list				*traverse;

	traverse = *node_in_edges(&info->graph, instr.node_id);
	while (traverse)
	{
		node_data = node_colony_data(&info->graph,
			edge_tail(&info->graph, LST_CONT(traverse, size_t)));
		if ((node_data->flags & START) || node_data->ant == instr.ant_id)
			return (edge_tail(&info->graph, LST_CONT(traverse, size_t)));
		traverse = traverse->next;
	}
	return (-1);
}

static void	execute_instruction(t_lemin *info)
{
	t_colony_node_data	*node_data;
	t_instruction		instruction;
	t_list				*pop;
	ssize_t				prev_node;

	pop = list_pop(&info->instructions);
	while(pop && LST_CONT(pop, t_instruction).flusher)
		pop = list_pop(&info->instructions);
	if (pop)
	{
		instruction = LST_CONT(pop, t_instruction);
		node_data = node_colony_data(&info->graph, instruction.node_id);
		/* TODO ant tree to make sure ant is in a node connected to node_id */
		if ((prev_node = instruction_is_valid(info, instruction)) >= 0)
		{
			ft_printf("%sInstruction valid%s: ant %zu to %s\n",
				ANSI_COLOR_GREEN, ANSI_COLOR_RESET,
				instruction.ant_id, node_data->name);
			node_data->ant = instruction.ant_id;
			node_colony_data(&info->graph, prev_node)->ant = 0;
		}
		else
			ft_printf("%sInstruction invalid%s: ant %zu to %s\n",
				ANSI_COLOR_RED, ANSI_COLOR_RESET,
				instruction.ant_id, node_data->name);
		/* TODO remove ants that get absorbed message if tree is empty*/
	}
	free(pop);
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
				; /*TODO*/
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
	else if (event->key.keysym.sym == SDLK_m && event->key.type == SDL_KEYDOWN)
		execute_instruction(info);
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
