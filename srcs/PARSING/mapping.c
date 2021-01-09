/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:08:27 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 10:12:05 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

const t_pars2	g_pars2[] =
{
	{ID_POS_NORTH, 10},
	{ID_POS_EAST, 11},
	{ID_POS_WEST, 12},
	{ID_POS_SOUTH, 13},
	{0, 0}
};

char	get_pos_id(int ref)
{
	size_t	i;

	i = 0;
	while (g_pars2[i].ref && g_pars2[i].ref != ref)
		i++;
	return (g_pars2[i].id);
}

int		get_pos_ref(char id)
{
	size_t	i;

	i = 0;
	while (g_pars2[i].id && g_pars2[i].id != id)
		i++;
	return (g_pars2[i].ref);
}

bool	fill_map(t_map *map, char *line, int y)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			map->map[i][y] = line[i] - 48;
			if (map->map[i][y] > 1)
			{
				if (!(add_sprite(map, i, y)))
					return (report(FAIL_SPRITE));
				add_needed_texture(map, line[i] - 48);
			}
		}
		else if (line[i] == 32)
			map->map[i][y] = VACANT;
		else if (!(map->map[i][y] = get_pos_ref(line[i])))
			return (report(FAIL_MISSING_PARS_ID));
		i++;
	}
	free(line);
	while (i < map->size_x)
		map->map[i++][y] = -1;
	return (true);
}

bool	pars_map(int fd, char *line, t_map *map)
{
	int		gnl;
	size_t	i;

	i = map->size_y - 1;
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			return (report5(FAIL_PARS_MAP, FAIL_GNL, 0, fd));
		else if (is_map_description(line) == true)
			break ;
		free(line);
	}
	if (!(map->map = alloc_map(map->size_x, map->size_y)))
		return (report5(FAIL_PARS_MAP, FAIL_MALLOC, line, fd));
	else if (!fill_map(map, line, i--))
		return (report3(FAIL_PARS_MAP, line, fd));
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			return (report5(FAIL_PARS_MAP, FAIL_GNL, 0, fd));
		else if (!fill_map(map, line, i--))
			return (report3(FAIL_PARS_MAP, line, fd));
	}
	return (map_check(map));
}

bool	set_map(int fd, char *line, t_map *map, char *filename)
{
	int	gnl;

	map->size_y = 1;
	map->size_x = ft_strlen(line);
	free(line);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			return (report5(FAIL_PARS_MAP, FAIL_GNL, 0, fd));
		else if (is_map_description(line) == false)
			return (report5(FAIL_INVALID_MAP, line, line, fd));
		map->size_y += 1;
		if (ft_strlen(line) > (size_t)map->size_x)
			map->size_x = ft_strlen(line);
		free(line);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (report(filename));
	return (pars_map(fd, line, map));
}
