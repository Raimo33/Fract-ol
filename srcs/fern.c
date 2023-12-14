/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fern.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:44:10 by craimond          #+#    #+#             */
/*   Updated: 2023/12/14 17:17:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

short	zoom_fern(int button, int x, int y, t_gdata *data)
{
	t_dcoord	mouse_fractal;

	mouse_fractal.x = (x - WIDTH / 2)
		* (fabs(data->fern_max.x - data->fern_min.x))
		/ WIDTH + (data->fern_max.x + data->fern_min.x) / 2;
	mouse_fractal.y = (HEIGHT / 2 - y)
		* (fabs(data->fern_max.y - data->fern_min.y))
		/ HEIGHT + (data->fern_max.y + data->fern_min.y) / 2;
	if (button == 4)
		update_fern_bounds(data, mouse_fractal, (1 / ZOOM));
	else
		update_fern_bounds(data, mouse_fractal, ZOOM);
	call_threads(data);
	return (0);
}

void	update_fern_bounds(t_gdata *data, t_dcoord adj_mouse, double factor)
{
	data->fern_min.x = (data->fern_min.x - adj_mouse.x) * factor + adj_mouse.x;
	data->fern_min.y = (data->fern_min.y - adj_mouse.y) * factor + adj_mouse.y;
	data->fern_max.x = (data->fern_max.x - adj_mouse.x) * factor + adj_mouse.x;
	data->fern_max.y = (data->fern_max.y - adj_mouse.y) * factor + adj_mouse.y;
}

void	reset_to_default(t_gdata *data)
{
	if (data->f == &apply_mandelbrot)
		data->center.x = -0.75;
	else
	{
		data->center.x = 0;
		if (data->f == NULL)
		{
			data->fern_max.x = STARTING_FERN_X_MAX;
			data->fern_max.y = STARTING_FERN_Y_MAX;
			data->fern_min.x = STARTING_FERN_X_MIN;
			data->fern_min.y = STARTING_FERN_Y_MIN;
		}
	}
	data->center.y = 0;
	set_roi_range(data);
	data->max_iter = STARTING_MAX_ITER;
}

void	*render_fern(t_tdata *thread_data)
{
	unsigned long	i;
	t_dcoord		new;
	t_icoord		pix;
	t_gdata			*data;

	if (thread_data->id != 0)
		return (NULL);
	data = thread_data->data;
	reset_image(data);
	new.x = 0;
	new.y = 0;
	i = -1;
	while (++i < FERN_ITERATIONS)
	{
		new = apply_fern(new);
		pix.x = (int)(((new.y - data->fern_min.x) * WIDTH
					/ (data->fern_max.x - data->fern_min.x)) / data->roi_range);
		pix.y = (int)((HEIGHT - ((new.x - data->fern_min.y) * HEIGHT
						/ (data->fern_max.y - data->fern_min.y)))
				/ data->roi_range);
		if (pix.y >= 0 && pix.x < WIDTH && pix.y >= 0 && pix.y < HEIGHT)
			my_mlx_pixel_put(data, pix.x, pix.y, 0x00FF00);
	}
	return (NULL);
}

void	reset_image(t_gdata *data)
{
	t_icoord	pix;

	pix.y = -1;
	while (++pix.y < HEIGHT)
	{
		pix.x = -1;
		while (++pix.x < WIDTH)
			my_mlx_pixel_put(data, pix.x, pix.y, 0x000000);
	}
}
