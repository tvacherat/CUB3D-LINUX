/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecking.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:25:53 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/05 16:27:17 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_player_starting_position(int value)
{
	char c;

	c = get_pos_id(value);
	if (c == ID_POS_NORTH || c == ID_POS_EAST
		|| c == ID_POS_WEST || c == ID_POS_SOUTH)
		return (true);
	return (false);
}

bool	is_wall_or_vacant(t_map *map, int x, int y)
{
	if (x < 0 || x == map->size_x || y < 0 || y == map->size_y)
		return (true);
	else if (map->map[x][y] == WALL || map->map[x][y] == VACANT)
		return (true);
	return (false);
}

bool	is_breach(t_map *map, int x, int y)
{
	if ((x == 0 || x == map->size_x - 1 || y == 0 || y == map->size_y - 1)
		&& map->map[x][y] != WALL && map->map[x][y] != VACANT)
		return (true);
	else if (map->map[x][y] == VACANT)
	{
		if (!(is_wall_or_vacant(map, x + 1, y))
			|| !(is_wall_or_vacant(map, x - 1, y))
			|| !(is_wall_or_vacant(map, x, y - 1))
			|| !(is_wall_or_vacant(map, x, y + 1)))
			return (true);
	}
	return (false);
}

bool	map_check(t_map *map)
{
	size_t	i;
	size_t	j;
	bool	ok;

	i = 0;
	ok = false;
	while (i < (size_t)map->size_x)
	{
		j = 0;
		while (j < (size_t)map->size_y)
		{
			if (is_breach(map, i, j))
				return (report2(FAIL_MAP_CHECK, FAIL_BREACH_FOUND));
			else if (is_player_starting_position(map->map[i][j]))
			{
				if (ok == true)
					return (report2(FAIL_MAP_CHECK, FAIL_MANY_POS));
				ok = true;
			}
			j++;
		}
		i++;
	}
	return (ok ? true : report2(FAIL_MAP_CHECK, FAIL_NO_POS));
}
