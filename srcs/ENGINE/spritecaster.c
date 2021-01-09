/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:45:01 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 16:08:18 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		dist_sprite_cmp(t_sprite *a, t_sprite *b)
{
	if (b->dist - a->dist > 0.0)
		return (1);
	else
		return (0);
}

void	dist_sprite_player(t_list *lst, t_vector pos)
{
	t_sprite	*sprite;
	t_list		*i;

	i = lst;
	while (i)
	{
		sprite = (t_sprite *)i->content;
		sprite->dist = pow(pos.x - sprite->pos.x, 2)
			+ pow(pos.y - sprite->pos.y, 2);
		i = i->next;
	}
	ft_lst_sort(&lst, &dist_sprite_cmp);
}

void	init_castsp(t_mlx_setup *setup, t_spritecast *cast)
{
	cast->pos.x = cast->sprite->pos.x - setup->player.pos.x;
	cast->pos.y = cast->sprite->pos.y - setup->player.pos.y;
	cast->inv_det = 1.0 / (setup->player.plane.x * setup->player.dir.y
		- setup->player.dir.x * setup->player.plane.y);
	cast->transform.x = cast->inv_det * (setup->player.dir.y * cast->pos.x
		- setup->player.dir.x * cast->pos.y);
	cast->transform.y = cast->inv_det * (-setup->player.plane.y * cast->pos.x
		+ setup->player.plane.x * cast->pos.y);
	cast->screen = (int)((setup->map->res_x / 2) * (1 + cast->transform.x
		/ cast->transform.y));
	cast->height = abs((int)(setup->map->res_y / cast->transform.y));
	cast->start.y = -cast->height / 2 + setup->map->res_y / 2;
	if (cast->start.y < 0)
		cast->start.y = 0;
	cast->end.y = cast->height / 2 + setup->map->res_y / 2;
	if (cast->end.y >= setup->map->res_y)
		cast->end.y = setup->map->res_y - 1;
	cast->width = abs((int)(setup->map->res_y / cast->transform.y));
	cast->start.x = -cast->width / 2 + cast->screen;
	if (cast->start.x < 0)
		cast->start.x = 0;
	cast->end.x = cast->width / 2 + cast->screen;
	if (cast->end.x >= setup->map->res_x)
		cast->end.x = setup->map->res_x - 1;
}

void	draw_sprite(t_mlx_setup *setup, t_spritecast *cast)
{
	int	i;
	int	j;

	i = cast->start.x - 1;
	while (++i < cast->end.x)
	{
		cast->tex.x = (int)(256 * (i - (-cast->width / 2 + cast->screen))
			* cast->sprite->texture->img.width / cast->width) / 256;
		if (cast->transform.y > 0 && i > 0 && i < setup->map->res_x
			&& cast->transform.y < setup->zbuff[i])
		{
			j = cast->start.y - 1;
			while (++j < cast->end.y)
			{
				cast->d = j * 256 - setup->map->res_y
					* 128 + cast->height * 128;
				cast->tex.y = ((cast->d * cast->sprite->texture->img.height)
					/ cast->height) / 256;
				cast->color = get_pixel(&cast->sprite->texture->img
					, cast->tex.x, cast->tex.y);
				if ((cast->color & 0x00FFFFFF) != 0)
					put_pixel(&setup->buff, i, j, cast->color);
			}
		}
	}
}

void	spritecast(t_mlx_setup *setup)
{
	t_list			*i;
	t_spritecast	cast;

	dist_sprite_player(setup->map->sprites, setup->player.pos);
	i = setup->map->sprites;
	while (i)
	{
		cast.sprite = (t_sprite *)i->content;
		init_castsp(setup, &cast);
		draw_sprite(setup, &cast);
		i = i->next;
	}
}
