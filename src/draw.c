/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:33:24 by zzaludov          #+#    #+#             */
/*   Updated: 2023/06/22 21:33:26 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	color_default(t_coord c0, t_coord c1, t_line line)
{
	int32_t	color;

	if (c1.x == line.x)
		color = c1.color;
	else
		color = c0.color;
	return (color);
}

double	position(t_coord c0, t_coord c1, t_line line, t_map *map)
{
	double	value;
	double	pos;

	if (c1.y - c0.y != 0)
		value = c0.z + (((line.y - c0.y) * (c1.z - c0.z)) / (c1.y - c0.y));
	else
		value = c1.z;
	if (map->min < 0)
		pos = (value - map->min) / (double)(map->max - map->min);
	else
		pos = value / (double)(map->max - map->min);
	return (pos);
}

void	draw_color(t_coord c0, t_coord c1, t_line line, t_pointer_mlx *p)
{
	int32_t	color;
	double	pos;

	color = 0;
	pos = position(c0, c1, line, p->map);
	if (p->color_mode == 0)
		color = color_default(c0, c1, line);
	else if (p->color_mode == 1)
		color = blue_gradient(pos);
	else if (p->color_mode == 2)
		color = aqua_gradient(pos);
	else if (p->color_mode == 3)
		color = purple_gradient(pos);
	else if (p->color_mode == 4)
		color = green_gradient(pos);
	else if (p->color_mode == 5)
		color = orange_gradient(pos);
	else if (p->color_mode == 6)
		color = pixel(rand() % 0xFF, rand() % 0xFF,
				rand() % 0xFF, rand() % 0xFF);
	if (line.x + (WIDTH / 2) > 0 && line.x + (WIDTH / 2) < WIDTH
		&& line.y + (HEIGHT / 2) > 0 && line.y + (HEIGHT / 2) < HEIGHT)
		mlx_put_pixel(p->img, line.x + (WIDTH / 2), line.y
			+ (HEIGHT / 2), color);
}
