/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:59:50 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 16:48:24 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool			is_tolerated_value(char c)
{
	if (c == ID_POS_NORTH || c == ID_POS_SOUTH || c == ID_POS_EAST
		|| c == ID_POS_WEST)
		return (true);
	if (ft_isdigit(c) && c - 48 <= MAP_MAX_VALUE)
		return (true);
	return (false);
}

void			check_win_size(t_map *map, void *mlx)
{
	int	size_x;
	int	size_y;

	mlx_get_screen_size(mlx, &size_x, &size_y);
	if (size_x < map->res_x)
		map->res_x = size_x;
	if (size_y < map->res_y)
		map->res_y = size_y;
}

void			put_pixel(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

unsigned int	get_pixel(t_img *img, int x, int y)
{
	char	*src;

	src = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}

bool			floor_exist(t_mlx_setup *setup)
{
	int				i;
	bool			floor;
	bool			ceiling;
	static short	ok = 0;

	if (ok == 1 || ok == -1)
		return (ok == 1 ? true : false);
	i = 0;
	floor = false;
	ceiling = false;
	while (setup->map->textures[i].id)
	{
		if (ft_strcmp(setup->map->textures[i].id, ID_TEX_FL) == 0)
			floor = setup->map->textures[i].path ? true : false;
		else if (ft_strcmp(setup->map->textures[i].id, ID_TEX_CL) == 0)
			ceiling = setup->map->textures[i].path ? true : false;
		i++;
	}
	if (floor == true && ceiling == true)
	{
		ok = 1;
		return (true);
	}
	ok = -1;
	return (false);
}
