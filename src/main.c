/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:34:14 by zzaludov          #+#    #+#             */
/*   Updated: 2023/05/12 20:34:22 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	zoom_height(t_map map, int zoom, int height)
{
	map.zoom = zoom;
	if (height == -1)
	{
		if (map.max - map.min < 10)
			map.height = 15;
		else if (map.max - map.min < 30)
			map.height = 4;
		else
			map.height = 1;
	}
	else
		map.height = height;
	return (map);
}

t_map	init_values(t_map map)
{
	if (map.w * map.h >= (WIDTH * HEIGHT) - 500)
		error_occur("Map size too big.");
	else if (map.w * map.h * 50 >= (WIDTH * HEIGHT) - 500
		&& map.w * map.h < (WIDTH * HEIGHT) - 500)
		map = zoom_height(map, 2, 1);
	else if (map.w * map.h * 100 >= (WIDTH * HEIGHT) - 500
		&& map.w * map.h * 50 < (WIDTH * HEIGHT) - 500)
		map = zoom_height(map, 3, 1);
	else if (map.w * map.h * 250 >= (WIDTH * HEIGHT) - 5000
		&& map.w * map.h * 100 < (WIDTH * HEIGHT) - 500)
		map = zoom_height(map, 5, 2);
	else if (map.w * map.h * 500 >= (WIDTH * HEIGHT) - 50000
		&& map.w * map.h * 250 < (WIDTH * HEIGHT) - 5000)
		map = zoom_height(map, 10, 5);
	else if (map.w * map.h * 1000 >= (WIDTH * HEIGHT) - 50000
		&& map.w * map.h * 500 < (WIDTH * HEIGHT) - 5000)
		map = zoom_height(map, 20, 5);
	else if (map.w * map.h * 1000 < (WIDTH * HEIGHT) - 50000)
		map = zoom_height(map, 30, -1);
	map.angle_x = 0;
	map.angle_y = 0;
	map.angle_z = 0;
	map.proj = 'i';
	return (map);
}

int32_t	main(int argc, char **argv)
{
	t_map			map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pointer_mlx	p;

	map = open_map(&map, argv[1]);
	map = init_values(map);
	if (argc > 2)
		error_occur("Incorrect number of arguments.");
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		error_occur("Inicialization failure.");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		error_occur("Image to window fail.");
	p.mlx = mlx;
	p.img = img;
	p.map = &map;
	p.color_mode = 0;
	mlx_loop_hook(mlx, bresenham, &p);
	mlx_loop_hook(mlx, keys, &p);
	mlx_loop(mlx);
	free_memory((void **) p.map->origin);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
