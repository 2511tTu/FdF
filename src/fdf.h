/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:30:34 by zzaludov          #+#    #+#             */
/*   Updated: 2023/07/11 21:08:04 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../FT_LIBRARY/ft_library.h"
# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_quaternion
{
	float	w;
	float	x;
	float	y;
	float	z;
}	t_quaternion;

typedef struct s_origin
{
	float			x;
	float			y;
	int				z;
	uint32_t		color;
}	t_origin;

typedef struct s_coord
{
	int			x;
	int			y;
	int			z;
	uint32_t	color;
}	t_coord;

typedef struct s_line
{
	int	y;
	int	x;
	int	xi;
	int	yi;
	int	dx;
	int	dy;
	int	lenght;
}	t_line;

typedef struct s_map
{
	int				fd_1;
	int				fd_2;
	int				h;
	int				w;
	int				min;
	int				max;
	int				zoom;
	int				height;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	char			proj;
	t_origin		**origin;
	t_coord			**coord;
	t_line			line;
	t_quaternion	rotation_x;
	t_quaternion	rotation_y;
	t_quaternion	rotation_z;
}	t_map;

typedef struct s_pointer_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	int				color_mode;
}	t_pointer_mlx;

t_map		open_map(t_map *map, char *file);
uint32_t	get_color(char *value);
void		error_occur(char *announcement);
void		free_memory(void **ptr);
void		alpha_screen(mlx_image_t *img);
void		projection(t_map *map);
void		rotation(t_map *map);
void		bresenham(void *param);
int32_t		pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void		draw_color(t_coord c0, t_coord c1, t_line line, t_pointer_mlx *p);
int32_t		blue_gradient(double pos);
int32_t		aqua_gradient(double pos);
int32_t		purple_gradient(double pos);
int32_t		green_gradient(double pos);
int32_t		orange_gradient(double pos);
void		keys(void *param);

#endif
