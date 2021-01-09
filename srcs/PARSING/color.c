/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:31:31 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 19:52:12 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

const char	*g_id_color[] =
{
	ID_COL_UP,
	ID_COL_GR,
	0
};

bool	only_digit(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (ft_isdigit(split[i][j]) == false)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_color(t_map *map, char *line, int i)
{
	size_t	j;
	int		rgb[3];
	char	**split;

	j = skip_id(line);
	if (!(split = ft_split(line + j, " ,")))
		return (report2(FAIL_COLOR_PARS, FAIL_MALLOC));
	if (ft_split_size(split) != 3 || only_digit(split) == false)
	{
		ft_free_split(split);
		return (report2(FAIL_COLOR_PARS, FAIL_WRONG_RGB));
	}
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255
		|| rgb[2] < 0 || rgb[2] > 255)
	{
		ft_free_split(split);
		return (report2(FAIL_COLOR_PARS, FAIL_WRONG_RGB));
	}
	ft_free_split(split);
	map->colors[i].color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	return (true);
}

bool	set_color(char *line, t_map *map)
{
	size_t	i;
	size_t	j;
	char	*id;
	int		nb_dot;

	i = skip_id(line);
	nb_dot = 0;
	while (line[i])
	{
		if (line[i++] == ',')
			nb_dot++;
	}
	if (nb_dot != 2)
		return (report2(FAIL_COLOR_PARS, FAIL_WRONG_RGB));
	j = 0;
	if (!(id = get_id(line)))
		return (report2(FAIL_COLOR_PARS, FAIL_MALLOC));
	while (map->colors[j].id && ft_strcmp(map->colors[j].id, id) != 0)
		j++;
	if (!map->colors[j].id)
		return (report4(FAIL_COLOR_PARS, FAIL_MISSING_COLOR_ID, id, 0));
	else if (map->colors[j].color != 0)
		return (report4(FAIL_COLOR_PARS, FAIL_COL_ALREADY_SET, id, 0));
	free(id);
	return (check_color(map, line, j));
}

bool	init_color(t_map *map)
{
	size_t	i;

	i = 0;
	map->colors = 0;
	while (g_id_color[i])
		i++;
	if (!(map->colors = malloc(sizeof(t_color) * (i + 1))))
		return (report(FAIL_MALLOC));
	i = 0;
	while (g_id_color[i])
	{
		if (!(map->colors[i].id = ft_strdup(g_id_color[i])))
			return (report(FAIL_MALLOC));
		map->colors[i].color = 0;
		i++;
	}
	map->colors[i].id = 0;
	map->colors[i].color = 0;
	return (true);
}

void	free_color(t_map *map)
{
	size_t	i;

	i = 0;
	if (map->colors)
	{
		while (map->colors[i].id)
		{
			map->colors[i].color = 0;
			free(map->colors[i].id);
			i++;
		}
		free(map->colors);
	}
}
