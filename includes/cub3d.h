/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 10:30:49 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 19:28:55 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include "define.h"
# include "struct.h"
# include "../libft/includes/libft.h"

/*
**	cub3d.c
*/
bool			launch_parsing(int argc, char **argv, t_map *map
				, bool *save_opt);
int				render(t_mlx_setup *setup);
bool			launch_cub(t_map *map, bool save_opt);
int				main(int argc, char **argv);
/*
**	PARSING/parsing.c
*/
bool			parsing(int fd, t_map *map, char *filename);
bool			check_arg(int argc, char **argv, int *fd, bool *save_opt);
bool			add_element(char *line, t_map *map);
bool			is_element(char *line);
bool			is_map_description(char *line);
/*
**	PARSING/map.c
*/
bool			check_min_map_infos(t_map *map);
bool			load_textures(t_map *map, void *mlx);
void			free_map(t_map *map);
bool			init_map(t_map *map);
bool			set_resolution(char *line, t_map *map);
/*
**	PARSING/texture.c
*/
void			add_needed_texture(t_map *map, int ref);
bool			set_texture(char *line, t_map *map);
bool			init_texture(t_map *map);
bool			check_texture(t_map *map, char *path, int i);
void			free_texture(t_map *map);
/*
**	PARSING/color.c
*/
bool			only_digit(char **split);
bool			check_color(t_map *map, char *line, int i);
bool			set_color(char *line, t_map *map);
bool			init_color(t_map *map);
void			free_color(t_map *map);
/*
**	PARSING/mapping.c
*/
bool			set_map(int fd, char *line, t_map *map, char *filename);
bool			pars_map(int fd, char *line, t_map *map);
bool			fill_map(t_map *map, char *line, int index);
char			get_pos_id(int ref);
int				get_pos_ref(char id);
/*
**	PARSING/mapchecking.c
*/
bool			is_player_starting_position(int value);
bool			is_wall_or_vacant(t_map *map, int x, int y);
bool			is_breach(t_map *map, int x, int y);
bool			map_check(t_map *map);
/*
**	ENGINE/raycaster.c
*/
void			launch_dda(t_map *map, t_ray *ray, t_player *player);
t_pixline		init_line(t_map *map, t_ray *ray, t_player *player);
char			*get_wallface_id(t_ray *ray, t_player *player);
t_img			get_img(t_map *map, t_pixline *line, t_ray *ray
				, t_player *player);
void			ray_casting(t_mlx_setup *setup);
/*
**	ENGINE/draw.c
*/
void			fill_img_row(t_mlx_setup *setup, t_pixline *line
				, t_ray *ray, int x);
void			draw_floor(t_mlx_setup *setup, int start, int x);
/*
**	ENGINE/struct.c
*/
t_point			set_point(int x, int y);
t_vector		set_vector(double x, double y);
void			set_player_view(t_mlx_setup *setup, char pos);
void			init_player(t_mlx_setup *setup);
t_ray			init_ray(double x, t_map *map, t_player *player);
/*
**	ENGINE/keys.c
*/
int				ft_key_hook(t_mlx_setup *setup);
int				ft_key_release(int keycode, t_mlx_setup *setup);
int				ft_key_press(int keycode, t_mlx_setup *setup);
int				close_win(t_mlx_setup *setup);
/*
**	ENGINE/move.c
*/
int				forward(t_mlx_setup *setup);
int				backward(t_mlx_setup *setup);
int				go_left(t_mlx_setup *setup);
int				go_right(t_mlx_setup *setup);
/*
**	ENGINE/rotate.c
*/
void			rotate(t_vector *vector, double angle);
int				rotate_left(t_mlx_setup *setup);
int				rotate_right(t_mlx_setup *setup);
/*
**	ENGINE/floorcaster.c
*/
void			floor_casting(t_mlx_setup *setup);
void			print_floor(t_mlx_setup *setup, t_floorcast *ray, int y);
void			init_floorcast(t_floorcast *ray);
t_img			get_img2(t_mlx_setup *setup, char *id);
/*
**	ENGINE/spritecaster.c
*/
void			spritecast(t_mlx_setup *setup);
void			draw_sprite(t_mlx_setup *setup, t_spritecast *cast);
void			init_castsp(t_mlx_setup *setup, t_spritecast *cast);
void			dist_sprite_player(t_list *lst, t_vector pos);
int				dist_sprite_cmp(t_sprite *a, t_sprite *b);
/*
**	UTILS/save.c
*/
void			write_header(t_mlx_setup *setup, int fd);
void			render_bmp(t_mlx_setup *setup, int fd);
void			save_img(t_mlx_setup *setup);
/*
**	UTILS/erroc.c
*/
bool			report(char *error);
bool			report2(char *error, char *txt);
bool			report3(char *error, char *to_free, int to_close);
bool			report4(char *error, char *txt, char *to_free, char *to_free2);
bool			report5(char *error, char *txt, char *to_free, int to_close);
/*
**	UTILS/utils.c
*/
size_t			skip_id(char *line);
char			*get_id(char *line);
bool			is_true_file(char *filename);
size_t			txt_len(char *str);
bool			is_only_spaces(char *str);
/*
**	UTILS/utils2.c
*/
bool			is_tolerated_value(char c);
void			check_win_size(t_map *map, void *mlx);
void			put_pixel(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_img *img, int x, int y);
bool			floor_exist(t_mlx_setup *setup);
/*
**	UTILS/utils3.c
*/
int				**alloc_map(int size_x, int size_y);
bool			add_sprite(t_map *map, int x, int y);
int				create_trgb(int t, int r, int g, int b);

#endif
