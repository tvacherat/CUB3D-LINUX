/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 19:01:48 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 15:57:21 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

const t_pars	g_ids[] =
{
	{ID_RES, &set_resolution},
	{ID_TEX_NO, &set_texture},
	{ID_TEX_SO, &set_texture},
	{ID_TEX_WE, &set_texture},
	{ID_TEX_EA, &set_texture},
	{ID_TEX_SP, &set_texture},
	{ID_TEX_TB, &set_texture},
	{ID_TEX_CL, &set_texture},
	{ID_TEX_FL, &set_texture},
	{ID_COL_UP, &set_color},
	{ID_COL_GR, &set_color},
	{0, 0}
};

bool	check_arg(int argc, char **argv, int *fd, bool *save_opt)
{
	char	*check;

	errno = 0;
	if (argc < 2)
		return (report(FAIL_NO_CONF_FILE));
	else if (argc > 3)
		return (report(FAIL_MANY_ARG));
	else if (!(check = ft_strrchr(argv[1], '.')))
		return (report2(argv[1], FAIL_INVALID_FILE));
	else if (ft_strcmp(".cub", check) != 0)
		return (report2(argv[1], FAIL_INVALID_FILE));
	else if (argc == 3 && ft_strcmp("--save", argv[2]) != 0)
		return (report2(argv[2], FAIL_INVALID_OPT));
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
		return (report(argv[1]));
	*save_opt = argc == 3 ? true : false;
	return (true);
}

bool	add_element(char *line, t_map *map)
{
	size_t	i;
	size_t	j;
	char	*id;

	i = 0;
	j = skip_id(line);
	if (!(line[j]))
		return (report(FAIL_BAD_CONF_FILE));
	if (!(id = get_id(line)))
		return (report(FAIL_MALLOC));
	while (ft_strcmp(id, g_ids[i].id) != 0)
		i++;
	free(id);
	if (g_ids[i].f(line, map) == false)
		return (report2(FAIL_WRONG_DESCRIPTION_LINE, line));
	return (true);
}

bool	is_map_description(char *line)
{
	size_t	i;
	bool	ok;

	i = 0;
	ok = false;
	while (line[i])
	{
		if (line[i] != 32 && !is_tolerated_value(line[i]))
			return (false);
		else if (ft_isdigit(line[i]))
			ok = true;
		i++;
	}
	return (ok);
}

bool	is_element(char *line)
{
	size_t	i;
	size_t	j;
	char	*id;

	i = 0;
	j = 0;
	while (line[i] && ft_isspace(line[i]) == false
		&& ft_isalpha(line[i]) == true)
		i++;
	if (i == 0 || i > 2 || ft_isspace(line[i]) == false)
		return (false);
	if (!(id = get_id(line)))
		return (report(FAIL_MALLOC));
	while (g_ids[j].id)
	{
		if (ft_strcmp(id, g_ids[j].id) == 0)
		{
			free(id);
			return (true);
		}
		j++;
	}
	free(id);
	return (false);
}

bool	parsing(int fd, t_map *map, char *filename)
{
	int		gnl;
	char	*line;

	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			return (report3(FAIL_GNL, 0, fd));
		else if (is_element(line) == true)
		{
			if (add_element(line, map) == false)
				return (report3(FAIL_PARS_ELEM, line, fd));
		}
		else if (is_map_description(line) == true)
		{
			if (set_map(fd, line, map, filename) == false)
				return (report(FAIL_PARS_MAP));
			break ;
		}
		else if (ft_strlen(line) > 0)
			return (report5(FAIL_BAD_CONF_FILE, line, line, fd));
		free(line);
	}
	close(fd);
	return (check_min_map_infos(map));
}
