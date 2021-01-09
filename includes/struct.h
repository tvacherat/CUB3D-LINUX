/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:07:30 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 18:17:45 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef struct	s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_texture
{
	char		*id;
	char		*path;
	bool		needed;
	t_img		img;
}				t_texture;

typedef struct	s_color
{
	char		*id;
	int			color;
}				t_color;

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_sprite
{
	t_texture	*texture;
	t_vector	pos;
	double		dist;
}				t_sprite;

typedef struct	s_map
{
	int			**map;
	int			size_x;
	int			size_y;
	int			res_x;
	int			res_y;
	t_color		*colors;
	t_texture	*textures;
	t_list		*sprites;
}				t_map;

typedef struct	s_pars
{
	char		*id;
	bool		(*f)(char *line, t_map *map);
}				t_pars;

typedef struct	s_pars2
{
	char		id;
	int			ref;
}				t_pars2;

typedef struct	s_pars3
{
	char		*id;
	int			ref;
}				t_pars3;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}				t_player;

typedef struct	s_ray
{
	double		camera_x;
	t_vector	ray_dir;
	t_point		map;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	t_point		step;
	bool		hit;
	int			side;
}				t_ray;

typedef struct	s_pixline
{
	int			height;
	int			start;
	int			end;
	int			tex_num;
	double		wall_x;
	t_img		img;
	int			tex_x;
}				t_pixline;

typedef struct	s_mlx_setup
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_player	player;
	t_img		buff;
	double		*zbuff;
}				t_mlx_setup;

typedef struct	s_key_event
{
	int			keycode;
	int			(*f)(t_mlx_setup *setup);
	bool		key_press;
}				t_key_event;

typedef struct	s_floorcast
{
	t_vector	dir_1;
	t_vector	dir_2;
	t_vector	step;
	t_vector	floor;
	t_point		cell;
	t_point		tex_f;
	t_point		tex_c;
	int			p;
	double		pos_z;
	double		row_dist;
	t_img		img_floor;
	t_img		img_ceiling;
}				t_floorcast;

typedef struct	s_spritecast
{
	t_sprite	*sprite;
	t_vector	pos;
	t_vector	transform;
	t_point		start;
	t_point		end;
	t_point		tex;
	double		inv_det;
	int			screen;
	int			height;
	int			width;
	int			d;
	int			color;
}				t_spritecast;

#endif
