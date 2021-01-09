/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:22:04 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 12:22:38 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rotate(t_vector *vector, double angle)
{
	double	i;
	double	j;
	double	k;

	i = vector->x;
	j = cos(angle);
	k = sin(angle);
	vector->x = vector->x * j - vector->y * k;
	vector->y = vector->y * j + i * k;
}

int		rotate_left(t_mlx_setup *setup)
{
	rotate(&setup->player.plane, ROT_SPEED / 180.0 * M_PI);
	rotate(&setup->player.dir, ROT_SPEED / 180.0 * M_PI);
	return (true);
}

int		rotate_right(t_mlx_setup *setup)
{
	rotate(&setup->player.plane, -ROT_SPEED / 180.0 * M_PI);
	rotate(&setup->player.dir, -ROT_SPEED / 180.0 * M_PI);
	return (true);
}
