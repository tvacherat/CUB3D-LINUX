/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:22:00 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 18:05:15 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	write_header(t_mlx_setup *setup, int fd)
{
	int	temp;

	write(fd, "BM", 2);
	temp = 54 + 4 * setup->map->res_x * setup->map->res_y;
	write(fd, &temp, 4);
	temp = 0;
	write(fd, &temp, 2);
	write(fd, &temp, 2);
	temp = 54;
	write(fd, &temp, 4);
	temp = 40;
	write(fd, &temp, 4);
	write(fd, &setup->map->res_x, 4);
	write(fd, &setup->map->res_y, 4);
	temp = 1;
	write(fd, &temp, 2);
	write(fd, &setup->buff.bpp, 2);
	temp = 0;
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
	write(fd, &temp, 4);
}

void	render_bmp(t_mlx_setup *setup, int fd)
{
	int	x;
	int	y;
	int	color;

	write_header(setup, fd);
	y = setup->map->res_y;
	while (y >= 0)
	{
		x = 0;
		while (x < setup->map->res_x)
		{
			color = get_pixel(&setup->buff, x, y);
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void	save_img(t_mlx_setup *setup)
{
	int	fd;

	setup->buff.img = mlx_new_image(setup->mlx, setup->map->res_x
	, setup->map->res_y);
	setup->buff.addr = mlx_get_data_addr(setup->buff.img, &setup->buff.bpp
	, &setup->buff.line_len, &setup->buff.endian);
	if (floor_exist(setup) && ACTIVE_RC)
		floor_casting(setup);
	ray_casting(setup);
	if (setup->map->sprites)
		spritecast(setup);
	fd = open(SAVE_NAME, O_WRONLY | O_CREAT, S_IRWXU | O_TRUNC);
	if (fd > 0)
		render_bmp(setup, fd);
	else
		report(FAIL_SAVE);
	mlx_destroy_image(setup->mlx, setup->buff.img);
	close_win(setup);
}
