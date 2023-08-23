/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradients.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:32:51 by zzaludov          #+#    #+#             */
/*   Updated: 2023/07/21 20:32:55 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	blue_gradient(double pos)
{
	double		r;
	double		g;
	double		b;
	int32_t		color;

	r = 66 - (pos * 51);
	g = 255 - (pos * 153);
	b = 255;
	color = pixel((int32_t)r, (int32_t)g, (int32_t)b, 255);
	return (color);
}

int32_t	aqua_gradient(double pos)
{
	double		r;
	double		g;
	double		b;
	int32_t		color;

	r = (pos * 255);
	g = 204 + (pos * 51);
	b = 255;
	color = pixel((int32_t)r, (int32_t)g, (int32_t)b, 255);
	return (color);
}

int32_t	purple_gradient(double pos)
{
	double		r;
	double		g;
	double		b;
	int32_t		color;

	r = 255 - (pos * 51);
	g = 204 - (pos * 204);
	b = 255 - (pos * 102);
	color = pixel((int32_t)r, (int32_t)g, (int32_t)b, 255);
	return (color);
}

int32_t	green_gradient(double pos)
{
	double		r;
	double		g;
	double		b;
	int32_t		color;

	r = 204 - (pos * 204);
	g = 255 - (pos * 153);
	b = 51;
	color = pixel((int32_t)r, (int32_t)g, (int32_t)b, 255);
	return (color);
}

int32_t	orange_gradient(double pos)
{
	double		r;
	double		g;
	double		b;
	int32_t		color;

	r = 255;
	g = (pos * 204);
	b = 0;
	color = pixel((int32_t)r, (int32_t)g, (int32_t)b, 255);
	return (color);
}
