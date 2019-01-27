/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:29:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/01/27 16:26:13 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "libft.h"
#include <SDL.h>

int		texture_from_file(SDL_Renderer *renderer, SDL_Texture **texture,
			const char *filename)
{
	SDL_Surface *image;

	image = SDL_LoadBMP(filename);
	if (!image)
		return (-1);
	(*texture) = SDL_CreateTextureFromSurface(renderer, image);
	if (!(*texture))
	{
		SDL_FreeSurface(image);
		return (-1);
	}
	SDL_FreeSurface(image);
	return (0);
}

int		init_textures(t_textures *textures)
{
	/*size_t	index;
	char	*digit_name;*/

	if (texture_from_file(textures->renderer,
		&textures->node, "resources/node.bmp") < 0)
		return (-1);
	if (texture_from_file(textures->renderer,
		&textures->start, "resources/start.bmp") < 0)
		return (-1);
	if (texture_from_file(textures->renderer,
		&textures->end, "resources/end.bmp") < 0)
		return (-1);
	/*index = 0;
	digit_name = ft_strdup("resources/0digit.bmp");
	while (index < 10)
	{
		digit_name[10] = '0' + index;
		if (texture_from_file(textures->renderer,
			&textures->digits[index], digit_name) < 0)
			return (-1);
		index++;
	}*/
	return (0);
}
