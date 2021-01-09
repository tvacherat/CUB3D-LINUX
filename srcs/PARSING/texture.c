/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 14:55:06 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 15:57:47 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

const t_pars3	g_id_texture[] =
{
	{ID_TEX_NO, WALL},
	{ID_TEX_SO, WALL},
	{ID_TEX_WE, WALL},
	{ID_TEX_EA, WALL},
	{ID_TEX_SP, SPRITE},
	{ID_TEX_TB, TABLE},
	{ID_TEX_CL, CEILING},
	{ID_TEX_FL, FLOOR},
	{0, 0}
};

void	add_needed_texture(t_map *map, int ref)
{
	size_t	i;

	i = 0;
	if (ref == WALL)
		return ;
	while (g_id_texture[i].ref != ref)
		i++;
	map->textures[i].needed = true;
}

bool	check_texture(t_map *map, char *path, int i)
{
	char	*check;

	map->textures[i].path = path;
	if (!(check = ft_strrchr(path, '.')))
		return (report2(path, FAIL_NO_XPM));
	else if (ft_strcmp(".xpm", check) != 0)
		return (report2(path, FAIL_NO_XPM));
	else if (is_true_file(map->textures[i].path) == false)
		return (report(map->textures[i].path));
	return (true);
}

bool	set_texture(char *line, t_map *map)
{
	size_t	i;
	size_t	j;
	char	*path;
	char	*id;

	i = skip_id(line);
	j = 0;
	if (is_only_spaces(line + i + txt_len(line + i)) == false)
		return (report2(FAIL_TEXTURE_PARS, FAIL_OTHER_2));
	if (!(path = malloc(sizeof(char) * (txt_len(line + i) + 1))))
		return (report2(FAIL_TEXTURE_PARS, FAIL_MALLOC));
	while (line[i] && ft_isspace(line[i]) == false)
		path[j++] = line[i++];
	path[j] = 0;
	if (!(id = get_id(line)))
		return (report4(FAIL_TEXTURE_PARS, FAIL_MALLOC, path, 0));
	i = 0;
	while (map->textures[i].id && ft_strcmp(map->textures[i].id, id) != 0)
		i++;
	if (!map->textures[i].id)
		return (report4(FAIL_TEXTURE_PARS, FAIL_MISSING_TEX_ID, path, id));
	else if (map->textures[i].path)
		return (report4(FAIL_TEXTURE_PARS, FAIL_TEXT_ALREADY_SET, path, id));
	free(id);
	return (check_texture(map, path, i));
}

bool	init_texture(t_map *map)
{
	size_t	i;

	i = 0;
	map->textures = 0;
	while (g_id_texture[i].id)
		i++;
	if (!(map->textures = malloc(sizeof(t_texture) * (i + 1))))
		return (report(FAIL_MALLOC));
	i = 0;
	while (g_id_texture[i].id)
	{
		if (!(map->textures[i].id = ft_strdup(g_id_texture[i].id)))
			return (report(FAIL_MALLOC));
		map->textures[i].path = 0;
		map->textures[i].needed = g_id_texture[i].ref == WALL ? true : false;
		i++;
	}
	map->textures[i].id = 0;
	map->textures[i].path = 0;
	map->textures[i].needed = false;
	return (true);
}

void	free_texture(t_map *map)
{
	size_t	i;

	i = 0;
	if (map->textures)
	{
		while (map->textures[i].id)
		{
			if (map->textures[i].path)
				free(map->textures[i].path);
			free(map->textures[i].id);
			i++;
		}
		free(map->textures);
	}
}
