/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:37:10 by zzaludov          #+#    #+#             */
/*   Updated: 2023/07/09 18:37:16 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (result);
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	t_quaternion	conjugate;

	conjugate.w = q.w;
	conjugate.x = -q.x;
	conjugate.y = -q.y;
	conjugate.z = -q.z;
	return (conjugate);
}

t_quaternion	quaternion_rotation(float angle, float axis_x,
	float axis_y, float axis_z)
{
	t_quaternion	rotation;
	float			half_angle;
	float			sin_half_angle;

	half_angle = angle / 2.0;
	sin_half_angle = sin(half_angle);
	rotation.w = cos(half_angle);
	rotation.x = axis_x * sin_half_angle;
	rotation.y = axis_y * sin_half_angle;
	rotation.z = axis_z * sin_half_angle;
	return (rotation);
}

t_coord	rotate_coord(t_coord coord, t_quaternion rotation)
{
	t_quaternion	pure_quat;
	t_quaternion	multiply;
	t_quaternion	conjugate;
	t_quaternion	rotated_quat;

	pure_quat.w = 0;
	pure_quat.x = (float)coord.x;
	pure_quat.y = (float)coord.y;
	pure_quat.z = 0;
	multiply = quaternion_multiply(rotation, pure_quat);
	conjugate = quaternion_conjugate(rotation);
	rotated_quat = quaternion_multiply(multiply, conjugate);
	coord.x = (int)rotated_quat.x;
	coord.y = (int)rotated_quat.y;
	return (coord);
}

void	rotation(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->rotation_x = quaternion_rotation(map->angle_x, 1.0, 0.0, 0.0);
	map->rotation_y = quaternion_rotation(map->angle_y, 0.0, 1.0, 0.0);
	map->rotation_z = quaternion_rotation(map->angle_z, 0.0, 0.0, 1.0);
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			map->coord[i][j] = rotate_coord(map->coord[i][j], map->rotation_x);
			map->coord[i][j] = rotate_coord(map->coord[i][j], map->rotation_y);
			map->coord[i][j] = rotate_coord(map->coord[i][j], map->rotation_z);
			j++;
		}
		i++;
	}
}
