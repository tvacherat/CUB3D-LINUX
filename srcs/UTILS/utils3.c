/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:45:33 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 19:27:57 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

extern const t_pars3	g_id_texture[];

int		**alloc_map(int size_x, int size_y)
{
	int	**map;
	int	i;

	i = 0;
	map = 0;
	if (!(map = malloc(sizeof(int *) * size_x)))
		return (0);
	while (i < size_x)
	{
		map[i] = 0;
		if (!(map[i] = malloc(sizeof(int) * size_y)))
			return (0);
		i++;
	}
	return (map);
}

bool	add_sprite(t_map *map, int x, int y)
{
	t_sprite	*sprite;
	int			i;
	char		*id;

	i = 0;
	if (!(sprite = malloc(sizeof(t_sprite))))
		return (report(FAIL_MALLOC));
	sprite->pos = set_vector(x + 0.5, y + 0.5);
	while (g_id_texture[i].ref != map->map[x][y])
		i++;
	if (!g_id_texture[i].ref)
		return (report(FAIL_MISSING_TEX_ID));
	id = g_id_texture[i].id;
	i = 0;
	while (map->textures[i].id && ft_strcmp(id, map->textures[i].id) != 0)
		i++;
	if (!map->textures[i].id)
		return (report(FAIL_MISSING_TEX_ID));
	sprite->texture = &map->textures[i];
	ft_lstadd_front(&map->sprites, ft_lstnew(sprite));
	return (true);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
