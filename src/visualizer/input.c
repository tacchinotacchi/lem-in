/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 23:26:04 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 22:43:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "ft_printf.h"

static void	handle_key(const SDL_Event *event, t_lemin *info,
				t_visualizer *vis, t_renderer *renderer)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		SDL_SetRelativeMouseMode(SDL_FALSE);
	else if (event->key.keysym.sym == SDLK_w)
		renderer->view.velocity[2] = (event->key.type == SDL_KEYDOWN) ?
		0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_s)
		renderer->view.velocity[2] = (event->key.type == SDL_KEYDOWN) ?
		-0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_a)
		renderer->view.velocity[0] = (event->key.type == SDL_KEYDOWN) ?
		0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_d)
		renderer->view.velocity[0] = (event->key.type == SDL_KEYDOWN) ?
		-0.05f : 0.f;
	else if (event->key.keysym.sym == SDLK_m && event->key.type == SDL_KEYDOWN)
		execute_line(info, renderer, 1);
	else if (event->key.keysym.sym == SDLK_p && event->key.type == SDL_KEYDOWN)
		execute_line(info, renderer, 0);
	else if (event->key.keysym.sym == SDLK_r && event->key.type == SDL_KEYDOWN)
		generate_coords(info, vis);
}

void		handle_event(const SDL_Event *event, t_lemin *info,
			t_visualizer *vis, t_renderer *renderer)
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
		handle_key(event, info, vis, renderer);
}

void		update_position(t_view *view)
{
	float	direction[3];

	ft_memcpy(direction, view->velocity, sizeof(float) * 3);
	rotate_vector(direction, -view->v_rotation, -view->r_rotation);
	view->position[0] += direction[0];
	view->position[1] += direction[1];
	view->position[2] += direction[2];
}
