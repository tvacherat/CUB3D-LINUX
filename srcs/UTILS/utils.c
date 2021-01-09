/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:48:00 by tvachera          #+#    #+#             */
/*   Updated: 2020/12/21 21:55:55 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

extern const char *g_id_texture[];

bool		is_only_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

size_t		txt_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]) == false)
		i++;
	return (i);
}

size_t		skip_id(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == false)
		i++;
	while (line[i] && ft_isspace(line[i]) == true)
		i++;
	return (i);
}

char		*get_id(char *line)
{
	char	*id;
	size_t	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]) == false && i < ID_MAX_LEN)
		i++;
	if (!(id = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]) == false && i < ID_MAX_LEN)
	{
		id[i] = line[i];
		i++;
	}
	id[i] = 0;
	return (id);
}

bool		is_true_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	fd > 0 ? close(fd) : 0;
	return (fd > 0 ? true : false);
}
