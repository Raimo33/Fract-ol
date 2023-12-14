/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:37:07 by craimond          #+#    #+#             */
/*   Updated: 2023/12/14 15:32:15 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t	ft_strlen(const char *c);

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	quit(char id, t_gdata *data)
{
	t_wdata	*win_data;

	if (data)
	{
		win_data = data->win_data;
		mlx_destroy_window(win_data->mlx, win_data->win);
		mlx_destroy_image(win_data->mlx, win_data->img);
		mlx_destroy_display(win_data->mlx);
		free(win_data->mlx);
	}
	exit(id);
}

int	press_x(t_gdata *data)
{
	quit(0, data);
	return (0);
}

double	ft_atod(char *str)
{
	double			res;
	double			dec;
	unsigned short	i;
	unsigned short	j;

	res = 0;
	dec = 0;
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
		res = res * 10 + (str[i++] - 48);
	j = i + 1;
	if (str[i] == '.')
		while (str[++i])
			dec = dec * 10 + (str[i] - 48);
	res += dec / pow(10, ft_strlen(str + j));
	if (str[0] == '-')
		return (res * -1);
	return (res);
}

size_t	ft_strlen(const char *c)
{
	size_t	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}
