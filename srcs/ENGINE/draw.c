/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 20:11:50 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 15:58:24 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_roof(t_mlx_setup *setup, int start, int x)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	if (floor_exist(setup) && ACTIVE_RC)
		return ;
	while (setup->map->colors[i].id && ft_strcmp(setup->map->colors[i].id
		, ID_COL_UP) != 0)
		i++;
	while (y < start)
	{
		put_pixel(&setup->buff, x, y, setup->map->colors[i].color);
		y++;
	}
}

void	draw_floor(t_mlx_setup *setup, int start, int x)
{
	int			i;
	int			y;

	i = 0;
	y = start;
	if (floor_exist(setup) && ACTIVE_RC)
		return ;
	while (setup->map->colors[i].id && ft_strcmp(setup->map->colors[i].id
		, ID_COL_GR) != 0)
		i++;
	while (y < setup->map->res_y)
	{
		if (x < setup->map->res_x && x > 0 && y < setup->map->res_y && y > 0)
			put_pixel(&setup->buff, x, y, setup->map->colors[i].color);
		y++;
	}
}

void	fill_img_row(t_mlx_setup *setup, t_pixline *line, t_ray *ray, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * line->img.height / line->height;
	tex_pos = (line->start - setup->map->res_y / 2 + line->height / 2) * step;
	draw_roof(setup, line->start, x);
	y = line->start;
	while (y < line->end)
	{
		tex_y = (int)tex_pos & (line->img.height - 1);
		tex_pos += step;
		color = get_pixel(&line->img, line->tex_x, tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&setup->buff, x, y, color);
		y++;
	}
	draw_floor(setup, line->end, x);
}
