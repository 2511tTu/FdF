/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:17:43 by zzaludov          #+#    #+#             */
/*   Updated: 2023/06/08 21:48:16 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	load_map(int line, int columns_number, char **read_values, t_map *map)
{
	int	i;

	i = 0;
	map->origin[line] = (t_origin *) malloc (columns_number * sizeof(t_origin));
	while (i < columns_number)
	{
		map->origin[line][i].z = ft_atoi(read_values[i]);
		map->origin[line][i].y = i - (columns_number / 2);
		map->origin[line][i].x = line - (map->h / 2);
		map->origin[line][i].color = get_color(read_values[i]);
		if (map->min > map->origin[line][i].z)
			map->min = map->origin[line][i].z;
		if (map->max < map->origin[line][i].z)
			map->max = map->origin[line][i].z;
		i++;
	}
}

void	allocate_lines(t_map *map)
{
	int		count_lines;
	char	*read_line;

	count_lines = 0;
	read_line = get_next_line(map->fd_1);
	while (read_line != NULL)
	{
		count_lines++;
		free(read_line);
		read_line = get_next_line(map->fd_1);
	}
	free(read_line);
	map->h = count_lines;
	map->origin = (t_origin **) malloc (sizeof(t_origin *)
			* (count_lines + 1));
}

void	read_map(t_map *map)
{
	char	*read_line;
	char	*trimmed_line;
	char	**read_values;
	int		count_lines;
	int		count_columns;

	count_lines = 0;
	count_columns = 0;
	read_line = get_next_line(map->fd_2);
	while (read_line != NULL)
	{
		trimmed_line = ft_strtrim(read_line, " \n");
		read_values = ft_split(trimmed_line, ' ');
		while (read_values[count_columns] != NULL)
			count_columns++;
		load_map(count_lines, count_columns, read_values, map);
		free(read_line);
		free(trimmed_line);
		free_memory((void **)read_values);
		read_line = get_next_line(map->fd_2);
		count_lines++;
	}
	map->origin[count_lines] = NULL;
	map->w = count_columns;
}

t_map	open_map(t_map *map, char *file)
{
	map->fd_1 = open(file, 0);
	if (map->fd_1 == -1)
		error_occur("Opening file failure.");
	map->fd_2 = open(file, 0);
	map->origin = NULL;
	map->coord = NULL;
	map->min = 2147483647;
	map->max = -2147483648;
	allocate_lines (map);
	read_map(map);
	close(map->fd_1);
	close(map->fd_2);
	return (*map);
}
