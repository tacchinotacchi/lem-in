/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 23:26:04 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/03 23:28:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	handle_key(const SDL_Event *event, t_view *view)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	else if (event->key.keysym.sym == SDLK_w)
		view->velocity[2] = (event->key.type == SDL_KEYDOWN) ? 0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_s)
		view->velocity[2] = (event->key.type == SDL_KEYDOWN) ? -0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_a)
		view->velocity[0] = (event->key.type == SDL_KEYDOWN) ? 0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_d)
		view->velocity[0] = (event->key.type == SDL_KEYDOWN) ? -0.05f : 0.f;
}

void	handle_event(const SDL_Event *event, t_view *view)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		view->v_rotation -= 0.001f * event->motion.xrel;
		view->v_rotation = fmod(view->v_rotation, PI * 2.f);
		view->r_rotation += 0.001f * event->motion.yrel;
		if (view->r_rotation > PI / 2.f)
			view->r_rotation = PI / 2.f;
		else if (view->r_rotation < -PI / 2.f)
			view->r_rotation = -PI / 2.f;
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		SDL_SetRelativeMouseMode(SDL_TRUE);
	else if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
	{
		handle_key(event, view);
	}
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
