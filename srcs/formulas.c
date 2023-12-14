/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:56:53 by craimond          #+#    #+#             */
/*   Updated: 2023/12/14 15:26:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_dcoord	apply_mandelbrot(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	(void)data;
	new.x = old.x * old.x - old.y * old.y + c.x;
	new.y = 2 * old.x * old.y + c.y;
	return (new);
}

t_dcoord	apply_julia(t_dcoord old, t_dcoord c, t_gdata *data)
{
	t_dcoord	new;

	if (old.x == 0 && old.y == 0)
	{
		old.x = c.x;
		old.y = c.y;
	}
	c.x = data->julia_c.x;
	c.y = data->julia_c.y;
	new.x = old.x * old.x - old.y * old.y + c.x;
	new.y = 2 * old.x * old.y + c.y;
	return (new);
}

t_dcoord	apply_fern(t_dcoord old)
{
	float		n;
	t_dcoord	new;

	n = rand() / (float)RAND_MAX;
	new.x = 0;
	if (n < 0.86 && n >= 0.1)
	{
		new.x = 0.85 * old.x + 0.04 * old.y;
		new.y = -0.04 * old.x + 0.85 * old.y + 1.6;
	}
	else if (n < 0.93 && n >= 0.86)
	{
		new.x = 0.2 * old.x - 0.26 * old.y;
		new.y = 0.23 * old.x + 0.22 * old.y + 1.6;
	}
	else if (n >= 0.93)
	{
		new.x = -0.15 * old.x + 0.28 * old.y;
		new.y = 0.26 * old.x + 0.24 * old.y + 0.44;
	}
	else
		new.y = 0.16 * old.y;
	return (new);
}
