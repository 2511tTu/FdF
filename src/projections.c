/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:01:33 by zzaludov          #+#    #+#             */
/*   Updated: 2023/07/03 19:01:41 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	isometric(t_origin origin, t_map *map)
{
	t_coord	iso;

	iso.x = - (float)((origin.x - origin.y)
			* (float)((sqrt(3.0) / 2) * map->zoom));
	iso.y = (float)((float)((origin.x + origin.y) * (float)(map->zoom / 2))
			- (float)(origin.z * (sqrt(3.0) / 2) * map->height));
	return (iso);
}

t_coord	dimetric(t_origin origin, t_map *map)
{
	t_coord	di;

	di.x = - (origin.x - origin.y) * map->zoom;
	di.y = (origin.x + origin.y - map->height * origin.z);
	return (di);
}

t_coord	cabinet(t_origin origin, t_map *map)
{
	t_coord	cab;

	cab.y = (float)(origin.x * map->zoom - origin.z
			* (1 / sqrt(2.0)) * (float)(map->height / 2));
	cab.x = (float)(origin.y * map->zoom - origin.z
			* (1 / sqrt(2.0)) * (float)(map->height / 2));
	return (cab);
}

void	projection(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->coord = malloc ((map->h + 1) * sizeof(t_coord));
	while (i < map->h)
	{
		j = 0;
		map->coord[i] = malloc (map->w * sizeof(t_coord));
		while (j < map->w)
		{
			if (map->proj == 'i')
				map->coord[i][j] = isometric(map->origin[i][j], map);
			else if (map->proj == 'c')
				map->coord[i][j] = cabinet(map->origin[i][j], map);
			else
				map->coord[i][j] = dimetric(map->origin[i][j], map);
			map->coord[i][j].z = map->origin[i][j].z;
			map->coord[i][j].color = map->origin[i][j].color;
			j++;
		}
		i++;
	}
	map->coord[i] = NULL;
}
