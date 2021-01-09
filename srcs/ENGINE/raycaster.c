/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:59:09 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 11:41:55 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		launch_dda(t_map *map, t_ray *ray, t_player *player)
{
	while (ray->hit == false)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (map->map[ray->map.x][ray->map.y] == WALL)
			ray->hit = true;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - player->pos.x
			+ (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - player->pos.y
			+ (1 - ray->step.y) / 2) / ray->ray_dir.y;
}

char		*get_wallface_id(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
	{
		if (player->pos.x < ray->map.x)
			return (ID_TEX_WE);
		else
			return (ID_TEX_EA);
	}
	else
	{
		if (player->pos.y < ray->map.y)
			return (ID_TEX_SO);
		else
			return (ID_TEX_NO);
	}
}

t_img		get_img(t_map *map, t_pixline *line, t_ray *ray, t_player *player)
{
	size_t	i;
	char	*id;

	i = 0;
	if (line->tex_num == WALL)
		id = get_wallface_id(ray, player);
	else if (line->tex_num == SPRITE)
		id = ID_TEX_SP;
	else
		exit(EXIT_FAILURE);
	while (map->textures[i].id && ft_strcmp(map->textures[i].id, id) != 0)
		i++;
	return (map->textures[i].img);
}

t_pixline	init_line(t_map *map, t_ray *ray, t_player *player)
{
	t_pixline	line;

	line.height = (int)(map->res_y / ray->perp_wall_dist);
	line.start = -line.height / 2 + map->res_y / 2;
	line.end = line.height / 2 + map->res_y / 2;
	if (line.start < 0)
		line.start = 0;
	if (line.end >= map->res_y)
		line.end = map->res_y - 1;
	line.tex_num = map->map[ray->map.x][ray->map.y];
	if (ray->side == 0)
		line.wall_x = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		line.wall_x = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	line.wall_x -= floor(line.wall_x);
	line.img = get_img(map, &line, ray, player);
	line.tex_x = (int)(line.wall_x * (double)line.img.width);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		line.tex_x = line.img.width - line.tex_x - 1;
	return (line);
}

void		ray_casting(t_mlx_setup *setup)
{
	int			x;
	t_ray		ray;
	t_pixline	line;

	x = 0;
	while (x < setup->map->res_x)
	{
		ray = init_ray(x, setup->map, &setup->player);
		launch_dda(setup->map, &ray, &setup->player);
		setup->zbuff[x] = ray.perp_wall_dist;
		line = init_line(setup->map, &ray, &setup->player);
		fill_img_row(setup, &line, &ray, x);
		x++;
	}
}
