/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:33:09 by zzaludov          #+#    #+#             */
/*   Updated: 2023/06/22 21:33:12 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_projection(t_pointer_mlx *p, char proj)
{
	p->map->proj = proj;
	p->map->angle_x = 0.0;
	p->map->angle_y = 0.0;
	p->map->angle_z = 0.0;
}

void	keys_rotation(t_pointer_mlx *p)
{
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_6))
		p->map->angle_x += 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_4))
		p->map->angle_x -= 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_8))
		p->map->angle_y += 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_2))
		p->map->angle_y -= 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_3))
		p->map->angle_z += 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_1))
		p->map->angle_z -= 0.0654;
	if (mlx_is_key_down(p->mlx, MLX_KEY_I))
		change_projection(p, 'i');
	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
		change_projection(p, 'd');
	if (mlx_is_key_down(p->mlx, MLX_KEY_C))
		change_projection(p, 'c');
}

void	keys_color_mode(t_pointer_mlx *p)
{
	if (mlx_is_key_down(p->mlx, MLX_KEY_0))
		p->color_mode = 0;
	if (mlx_is_key_down(p->mlx, MLX_KEY_1))
		p->color_mode = 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_2))
		p->color_mode = 2;
	if (mlx_is_key_down(p->mlx, MLX_KEY_3))
		p->color_mode = 3;
	if (mlx_is_key_down(p->mlx, MLX_KEY_4))
		p->color_mode = 4;
	if (mlx_is_key_down(p->mlx, MLX_KEY_5))
		p->color_mode = 5;
	if (mlx_is_key_down(p->mlx, MLX_KEY_6))
		p->color_mode = 6;
}

void	keys(void *param)
{
	t_pointer_mlx	*p;

	p = param;
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(p->mlx);
	if (mlx_is_key_down(p->mlx, MLX_KEY_UP))
		p->img->instances[0].y -= 5;
	if (mlx_is_key_down(p->mlx, MLX_KEY_DOWN))
		p->img->instances[0].y += 5;
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		p->img->instances[0].x -= 5;
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		p->img->instances[0].x += 5;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_ADD))
		p->map->zoom += 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_SUBTRACT))
		p->map->zoom -= 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_MULTIPLY))
		p->map->height += 1;
	if (mlx_is_key_down(p->mlx, MLX_KEY_KP_DIVIDE))
		p->map->height -= 1;
	keys_rotation(p);
	keys_color_mode(p);
}
