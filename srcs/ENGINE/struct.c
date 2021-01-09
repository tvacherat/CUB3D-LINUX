/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 11:56:39 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 16:30:34 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_point		set_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

t_vector	set_vector(double x, double y)
{
	t_vector vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

void		set_player_view(t_mlx_setup *setup, char pos)
{
	if (pos == ID_POS_NORTH)
	{
		setup->player.dir = set_vector(0.0, 1.0);
		setup->player.plane = set_vector(ANGLE, 0.0);
	}
	else if (pos == ID_POS_SOUTH)
	{
		setup->player.dir = set_vector(0.0, -1.0);
		setup->player.plane = set_vector(-ANGLE, 0);
	}
	else if (pos == ID_POS_WEST)
	{
		setup->player.dir = set_vector(-1.0, 0.0);
		setup->player.plane = set_vector(0, ANGLE);
	}
	else if (pos == ID_POS_EAST)
	{
		setup->player.dir = set_vector(1.0, 0.0);
		setup->player.plane = set_vector(0.0, -ANGLE);
	}
}

void		init_player(t_mlx_setup *setup)
{
	int		i;
	int		j;

	i = 0;
	while (i < setup->map->size_x)
	{
		j = 0;
		while (j < setup->map->size_y)
		{
			if (is_player_starting_position(setup->map->map[i][j]))
			{
				set_player_view(setup, get_pos_id(setup->map->map[i][j]));
				setup->player.pos = set_vector(i + 0.5, j + 0.5);
				setup->map->map[i][j] = 0;
				return ;
			}
			j++;
		}
		i++;
	}
}

t_ray		init_ray(double x, t_map *map, t_player *player)
{
	t_ray	ray;

	ray.camera_x = 2 * x / (double)map->res_x - 1;
	ray.ray_dir.x = player->dir.x + player->plane.x * ray.camera_x;
	ray.ray_dir.y = player->dir.y + player->plane.y * ray.camera_x;
	ray.map = set_point(player->pos.x, player->pos.y);
	ray.delta_dist.x = sqrt(1 + pow(ray.ray_dir.y, 2) / pow(ray.ray_dir.x, 2));
	ray.delta_dist.y = sqrt(1 + pow(ray.ray_dir.x, 2) / pow(ray.ray_dir.y, 2));
	ray.hit = false;
	ray.step.x = ray.ray_dir.x < 0 ? -1 : 1;
	ray.side_dist.x = ray.ray_dir.x < 0 ? (player->pos.x - ray.map.x)
	* ray.delta_dist.x : (ray.map.x + 1.0 - player->pos.x) * ray.delta_dist.x;
	ray.step.y = ray.ray_dir.y < 0 ? -1 : 1;
	ray.side_dist.y = ray.ray_dir.y < 0 ? (player->pos.y - ray.map.y)
	* ray.delta_dist.y : (ray.map.y + 1.0 - player->pos.y) * ray.delta_dist.y;
	return (ray);
}
