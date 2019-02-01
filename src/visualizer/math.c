/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 18:11:11 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/01 20:16:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visualizer.h"

float	ft_fmod(float x, float mod)
{
	uint64_t	times;

	times = x / mod;
	return (x - mod * times);
}

float	ft_cos(float x)
{
	float term;
	float term_squared;
	float result;

	term = ft_fmod(x + PI, PI * 2) - PI;
	term_squared = term * term;
	term = term_squared;
	result = 1.f;
	result += -term/2.f;
	term *= term_squared;
	result += term/24.f;
	term *= term_squared;
	result += -term/720.f;
	term *= term_squared;
	result += term/40320.f;
	term *= term_squared;
	result += -term/3628800.f;
	term *= term_squared;
	result += term/479001600.f;
	term *= term_squared;
	result += -term/87178291200.f;
	return (result);
}

float	ft_sin(float x)
{
	float term;
	float term_squared;
	float result;

	term = ft_fmod(x + PI, PI * 2) - PI;
	term_squared = term * term;
	result = 0.f;
	result += term;
	term *= term_squared;
	result += -term/6.f;
	term *= term_squared;
	result += term/120.f;
	term *= term_squared;
	result += -term/5040.f;
	term *= term_squared;
	result += term/362880.f;
	term *= term_squared;
	result += -term/39916800.f;
	term *= term_squared;
	result += term/6227020800.f;
	term *= term_squared;
	result += -term/1307674368000.f;
	return (result);
}
