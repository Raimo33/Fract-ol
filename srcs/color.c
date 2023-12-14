/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 01:26:42 by claudio           #+#    #+#             */
/*   Updated: 2023/12/14 15:26:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_color(t_gdata *data, int x, int y, unsigned short intensity)
{
	t_color			color;
	unsigned int	color_hex;

	if (data->frequency > 0.5)
		data->frequency = 0.1;
	if (intensity >= (int)data->max_iter)
		color_hex = 0x000000;
	else
	{
		color.red = sin(data->frequency * intensity + 0) * 127 + 128;
		color.blue = sin(data->frequency * intensity + 2 * PI / 3) * 127 + 128;
		color.green = sin(data->frequency * intensity + 4 * PI / 3) * 127 + 128;
		color_hex = ((int)color.red << 16) | ((int)color.green << 8)
			| (int)color.blue;
	}
	my_mlx_pixel_put(data, x, y, color_hex);
}

void	my_mlx_pixel_put(t_gdata *data, int x, int y, unsigned int color)
{
	int	index;

	index = y * data->win_data->line_length
		+ x * (data->win_data->bits_per_pixel / 8);
	data->win_data->addr[index] = color & 0xFF;
	data->win_data->addr[index + 1] = (color >> 8) & 0xFF;
	data->win_data->addr[index + 2] = (color >> 16) & 0xFF;
}
