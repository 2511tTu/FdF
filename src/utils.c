/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:17:21 by zzaludov          #+#    #+#             */
/*   Updated: 2023/07/12 19:17:26 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_occur(char *announcement)
{
	ft_printf("%s\n", announcement);
	exit(EXIT_FAILURE);
}

void	free_memory(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	alpha_screen(mlx_image_t *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, 0xFFFFFF00);
			x++;
		}
		y++;
	}
}

uint32_t	atoi_color(char *value)
{
	int			i;
	int			digit;
	uint32_t	color;

	if (value[0] == '0' && value[1] == 'x')
		value += 2;
	i = 0;
	color = 0;
	while (value[i] != '\0')
	{
		if (value[i] >= '0' && value[i] <= '9')
			digit = value[i] - '0';
		else if (value[i] >= 'A' && value[i] <= 'F')
			digit = value[i] - 'A' + 10;
		else if (value[i] >= 'a' && value[i] <= 'f')
			digit = value[i] - 'a' + 10;
		else
			error_occur("Wrong color code.");
		color = (color << 4) | digit;
		i++;
	}
	return (color);
}

uint32_t	get_color(char *value)
{
	uint32_t	color;
	char		*temp;

	temp = ft_strchr(value, ',');
	if (temp != NULL)
	{
		temp = temp + 1;
		color = atoi_color(temp);
	}
	else
		color = 0xFFFFFFFF;
	return (color);
}
