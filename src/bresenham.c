/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:35:54 by zzaludov          #+#    #+#             */
/*   Updated: 2023/06/24 21:35:58 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line_high(t_coord c0, t_coord c1, t_line line, t_pointer_mlx *p)
{
	line.dx = c1.x - c0.x;
	line.dy = c1.y - c0.y;
	if (line.dx < 0)
	{
		line.xi = -1;
		line.dx = -line.dx;
	}
	line.lenght = (2 * line.dx) - line.dy;
	line.y = c0.y;
	line.x = c0.x;
	while (line.y <= c1.y)
	{
		if (line.x < WIDTH && line.y < HEIGHT)
			draw_color(c0, c1, line, p);
		if (line.lenght > 0)
		{
			line.x = line.x + line.xi;
			line.lenght = line.lenght + (2 * (line.dx - line.dy));
		}
		else
			line.lenght = line.lenght + (2 * line.dx);
		line.y++;
	}
}

void	plot_line_low(t_coord c0, t_coord c1, t_line line, t_pointer_mlx *p)
{
	line.dx = c1.x - c0.x;
	line.dy = c1.y - c0.y;
	if (line.dy < 0)
	{
		line.yi = -1;
		line.dy = -line.dy;
	}
	line.lenght = (2 * line.dy) - line.dx;
	line.y = c0.y;
	line.x = c0.x;
	while (line.x <= c1.x)
	{
		if (line.x < WIDTH && line.y < HEIGHT)
			draw_color(c0, c1, line, p);
		if (line.lenght > 0)
		{
			line.y = line.y + line.yi;
			line.lenght = line.lenght + (2 * (line.dy - line.dx));
		}
		else
			line.lenght = line.lenght + (2 * line.dy);
		line.x++;
	}
}

void	plot_line(t_coord c0, t_coord c1, t_pointer_mlx	*p)
{
	t_line	line;

	line.xi = 1;
	line.yi = 1;
	if (abs(c1.y - c0.y) < abs(c1.x - c0.x))
	{
		if (c0.x > c1.x)
			plot_line_low(c1, c0, line, p);
		else
			plot_line_low(c0, c1, line, p);
	}
	else
	{
		if (c0.y > c1.y)
			plot_line_high(c1, c0, line, p);
		else
			plot_line_high(c0, c1, line, p);
	}
}

void	bresenham(void *param)
{
	int				i;
	int				j;
	t_pointer_mlx	*p;

	i = -1;
	p = param;
	projection(p->map);
	rotation(p->map);
	alpha_screen(p->img);
	while (++i < p->map->h)
	{
		j = -1;
		while (++j < p->map->w)
		{
			if (i < p->map->h - 1)
				plot_line(p->map->coord[i][j], p->map->coord[i + 1][j], p);
			if (j < p->map->w - 1)
				plot_line(p->map->coord[i][j], p->map->coord[i][j + 1], p);
		}
	}
	free_memory((void **) p->map->coord);
}
