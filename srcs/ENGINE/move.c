/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:21:42 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 17:07:16 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		forward(t_mlx_setup *setup)
{
	if (setup->map->map[(int)(setup->player.pos.x + setup->player.dir.x
		* (MOVESPEED * 2))][(int)(setup->player.pos.y)] == 0)
		setup->player.pos.x += setup->player.dir.x * MOVESPEED;
	if (setup->map->map[(int)(setup->player.pos.x)][(int)(setup->player.pos.y
		+ setup->player.dir.y * (MOVESPEED * 2))] == 0)
		setup->player.pos.y += setup->player.dir.y * MOVESPEED;
	return (1);
}

int		backward(t_mlx_setup *setup)
{
	if (setup->map->map[(int)(setup->player.pos.x - setup->player.dir.x
		* (MOVESPEED * 2))][(int)(setup->player.pos.y)] == 0)
		setup->player.pos.x -= setup->player.dir.x * MOVESPEED;
	if (setup->map->map[(int)(setup->player.pos.x)][(int)(setup->player.pos.y
		- setup->player.dir.y * (MOVESPEED * 2))] == 0)
		setup->player.pos.y -= setup->player.dir.y * MOVESPEED;
	return (1);
}

int		go_right(t_mlx_setup *setup)
{
	if (setup->map->map[(int)(setup->player.pos.x + setup->player.dir.y
		* (MOVESPEED * 2))][(int)(setup->player.pos.y)] == 0)
		setup->player.pos.x += setup->player.dir.y * MOVESPEED;
	if (setup->map->map[(int)(setup->player.pos.x)][(int)(setup->player.pos.y
		- setup->player.dir.x * (MOVESPEED * 2))] == 0)
		setup->player.pos.y -= setup->player.dir.x * MOVESPEED;
	return (1);
}

int		go_left(t_mlx_setup *setup)
{
	if (setup->map->map[(int)(setup->player.pos.x - setup->player.dir.y
		* (MOVESPEED * 2))][(int)(setup->player.pos.y)] == 0)
		setup->player.pos.x -= setup->player.dir.y * MOVESPEED;
	if (setup->map->map[(int)(setup->player.pos.x)][(int)(setup->player.pos.y
		+ setup->player.dir.x * (MOVESPEED * 2))] == 0)
		setup->player.pos.y += setup->player.dir.x * MOVESPEED;
	return (1);
}
