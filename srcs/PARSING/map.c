/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:45:40 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 19:57:15 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_min_map_infos(t_map *map)
{
	size_t	i;

	i = 0;
	if (!map->map)
		return (report2(FAIL_MIN_INFOS, FAIL_MISS_MAP));
	else if (!map->res_x || !map->res_y)
		return (report2(FAIL_MIN_INFOS, FAIL_MISS_RES));
	while (map->textures[i].id)
	{
		if (map->textures[i].needed && !map->textures[i].path)
			return (report2(FAIL_MIN_INFOS, FAIL_MISS_TEX));
		i++;
	}
	return (true);
}

bool	set_resolution(char *line, t_map *map)
{
	size_t	i;

	i = skip_id(line);
	if (map->res_x != 0 || map->res_y != 0)
		return (report2(FAIL_RESOLUTION_PARS, FAIL_RESOLUTION_ALREADY_SET));
	while (line[i] && (ft_isspace(line[i]) || ft_isdigit(line[i])))
		i++;
	if (line[i])
		return (report2(FAIL_RESOLUTION_PARS, FAIL_OTHER_1));
	i = skip_id(line);
	while (ft_isdigit(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (report(FAIL_RESOLUTION_PARS));
	map->res_x = ft_atoi(line + skip_id(line));
	map->res_y = ft_atoi(line + i);
	if (map->res_x <= 0 || map->res_y <= 0)
		return (report2(FAIL_RESOLUTION_PARS, FAIL_WRONG_RESOLUTION));
	return (true);
}

bool	load_textures(t_map *map, void *mlx)
{
	size_t		i;
	t_texture	*textures;

	i = 0;
	textures = map->textures;
	while (map->textures[i].id)
	{
		if (map->textures[i].path)
		{
			if (!(map->textures[i].img.img = mlx_xpm_file_to_image(mlx
			, map->textures[i].path, &map->textures[i].img.width
			, &map->textures[i].img.height)))
				return (report2(map->textures[i].path, FAIL_NO_IMG));
			textures[i].img.addr = mlx_get_data_addr(map->textures[i].img.img
			, &map->textures[i].img.bpp
			, &map->textures[i].img.line_len
			, &map->textures[i].img.endian);
		}
		else
			map->textures[i].img.img = 0;
		i++;
	}
	return (true);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		while (i < map->size_x)
		{
			map->map[i] ? free(map->map[i]) : 0;
			i++;
		}
		free(map->map);
	}
	if (map->sprites)
		ft_lstclear(&map->sprites, &free);
	free_texture(map);
	free_color(map);
}

bool	init_map(t_map *map)
{
	map->map = 0;
	map->size_x = 0;
	map->size_y = 0;
	map->res_x = 0;
	map->res_y = 0;
	map->sprites = 0;
	if (init_texture(map) == false)
		return (report2(FAIL_INIT, FAIL_MALLOC));
	if (init_color(map) == false)
		return (report2(FAIL_INIT, FAIL_MALLOC));
	return (true);
}
