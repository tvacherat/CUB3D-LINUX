/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcaster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:26:14 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 16:54:12 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_img	get_img2(t_mlx_setup *setup, char *id)
{
	int	i;

	i = 0;
	while (setup->map->textures[i].id
		&& ft_strcmp(setup->map->textures[i].id, id) != 0)
		i++;
	return (setup->map->textures[i].img);
}

void	init_floorcast(t_floorcast *ray)
{
	ray->cell.x = (int)ray->floor.x;
	ray->cell.y = (int)ray->floor.y;
	ray->tex_f.x = (int)(ray->img_floor.width * (ray->floor.x - ray->cell.x))
	& (ray->img_floor.width - 1);
	ray->tex_f.y = (int)(ray->img_floor.height * (ray->floor.y - ray->cell.y))
	& (ray->img_floor.height - 1);
	ray->tex_c.x = (int)(ray->img_ceiling.width * (ray->floor.x - ray->cell.x))
	& (ray->img_ceiling.width - 1);
	ray->tex_c.y = (int)(ray->img_ceiling.height * (ray->floor.y
	- ray->cell.y)) & (ray->img_ceiling.height - 1);
	ray->floor.x += ray->step.x;
	ray->floor.y += ray->step.y;
}

void	print_floor(t_mlx_setup *setup, t_floorcast *ray, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < setup->map->res_x)
	{
		init_floorcast(ray);
		color = get_pixel(&ray->img_floor, ray->tex_f.x, ray->tex_f.y);
		color = (color >> 1) & 8355711;
		put_pixel(&setup->buff, x, y, color);
		color = get_pixel(&ray->img_ceiling, ray->tex_c.x, ray->tex_c.y);
		color = (color >> 1) & 8355711;
		put_pixel(&setup->buff, x, setup->map->res_y - y - 1, color);
		x++;
	}
}

void	floor_casting(t_mlx_setup *setup)
{
	int			y;
	t_floorcast	ray;

	y = 0;
	ray.dir_1.x = setup->player.dir.x - setup->player.plane.x;
	ray.dir_1.y = setup->player.dir.y - setup->player.plane.y;
	ray.dir_2.x = setup->player.dir.x + setup->player.plane.x;
	ray.dir_2.y = setup->player.dir.y + setup->player.plane.y;
	ray.img_floor = get_img2(setup, ID_TEX_FL);
	ray.img_ceiling = get_img2(setup, ID_TEX_CL);
	ray.pos_z = 0.5 * setup->map->res_y;
	while (y < setup->map->res_y)
	{
		ray.p = y - setup->map->res_y / 2;
		ray.row_dist = ray.pos_z / ray.p;
		ray.step.x = ray.row_dist * (ray.dir_2.x - ray.dir_1.x)
		/ setup->map->res_x;
		ray.step.y = ray.row_dist * (ray.dir_2.y - ray.dir_1.y)
		/ setup->map->res_x;
		ray.floor.x = setup->player.pos.x + ray.row_dist * ray.dir_1.x;
		ray.floor.y = setup->player.pos.y + ray.row_dist * ray.dir_1.y;
		print_floor(setup, &ray, y);
		y++;
	}
}
