/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 11:46:37 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 18:46:46 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	launch_parsing(int argc, char **argv, t_map *map, bool *save_opt)
{
	int	fd;

	if (check_arg(argc, argv, &fd, save_opt) == false)
		return (false);
	if (init_map(map) == false)
		return (false);
	if (parsing(fd, map, argv[1]) == false)
	{
		free_map(map);
		return (false);
	}
	return (true);
}

int		render(t_mlx_setup *setup)
{
	setup->buff.img = mlx_new_image(setup->mlx, setup->map->res_x
	, setup->map->res_y);
	setup->buff.addr = mlx_get_data_addr(setup->buff.img, &setup->buff.bpp
	, &setup->buff.line_len, &setup->buff.endian);
	if (floor_exist(setup) && ACTIVE_RC)
		floor_casting(setup);
	ray_casting(setup);
	if (setup->map->sprites)
		spritecast(setup);
	mlx_put_image_to_window(setup->mlx, setup->win, setup->buff.img, 0, 0);
	mlx_destroy_image(setup->mlx, setup->buff.img);
	ft_key_hook(setup);
	return (true);
}

bool	launch_cub(t_map *map, bool save_opt)
{
	t_mlx_setup	setup;

	setup.mlx = mlx_init();
	if (save_opt == false)
		check_win_size(map, setup.mlx);
	if (load_textures(map, setup.mlx) == false
		|| !(setup.zbuff = malloc(sizeof(double) * map->res_x)))
		return (false);
	setup.map = map;
	setup.buff.img = 0;
	setup.win = 0;
	init_player(&setup);
	if (save_opt == true)
		save_img(&setup);
	setup.win = mlx_new_window(setup.mlx, map->res_x, map->res_y, "Cub3D");
	mlx_hook(setup.win, 33, 1L << 17, &close_win, &setup);
	mlx_hook(setup.win, 2, 1L << 0, ft_key_press, &setup);
	mlx_hook(setup.win, 3, 1L << 1, ft_key_release, &setup);
	mlx_loop_hook(setup.mlx, &render, &setup);
	mlx_loop(setup.mlx);
	return (true);
}

int		main(int argc, char **argv)
{
	bool	save_opt;
	t_map	map;

	if (launch_parsing(argc, argv, &map, &save_opt) == false)
		return (EXIT_FAILURE);
	if (launch_cub(&map, save_opt) == false)
		return (EXIT_FAILURE);
	free_map(&map);
	return (EXIT_SUCCESS);
}
