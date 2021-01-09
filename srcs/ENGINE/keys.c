/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 13:52:03 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 17:24:19 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_key_event	g_key_event[] =
{
	{KEY_ESC, &close_win, false},
	{KEY_FRONT, &forward, false},
	{KEY_BACK, &backward, false},
	{KEY_LEFT, &go_left, false},
	{KEY_RIGHT, &go_right, false},
	{KEY_ROT_L, &rotate_left, false},
	{KEY_ROT_R, &rotate_right, false},
	{0, 0, false}
};

int		ft_key_press(int keycode, t_mlx_setup *setup)
{
	int	i;

	i = 0;
	(void)setup;
	while (g_key_event[i].keycode && g_key_event[i].keycode != keycode)
		i++;
	g_key_event[i].key_press = true;
	return (true);
}

int		ft_key_release(int keycode, t_mlx_setup *setup)
{
	int	i;

	i = 0;
	(void)setup;
	while (g_key_event[i].keycode && g_key_event[i].keycode != keycode)
		i++;
	g_key_event[i].key_press = false;
	return (true);
}

int		ft_key_hook(t_mlx_setup *setup)
{
	int	i;

	i = 0;
	while (g_key_event[i].keycode)
	{
		if (g_key_event[i].key_press == true)
			g_key_event[i].f(setup);
		i++;
	}
	return (true);
}

int		close_win(t_mlx_setup *setup)
{
	size_t	i;

	i = 0;
	while (setup->map->textures[i].id)
	{
		if (setup->map->textures[i].img.img)
			mlx_destroy_image(setup->mlx, setup->map->textures[i].img.img);
		i++;
	}
	free_map(setup->map);
	free(setup->zbuff);
	if (setup->win)
		mlx_destroy_window(setup->mlx, setup->win);
	exit(EXIT_SUCCESS);
	return (true);
}
