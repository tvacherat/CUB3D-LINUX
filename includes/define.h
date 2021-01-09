/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvachera <tvacherat@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:07:07 by tvachera          #+#    #+#             */
/*   Updated: 2021/01/07 19:53:31 by tvachera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define FAIL "Error"
# define FAIL_NO_CONF_FILE "Configuration file is missing"
# define FAIL_MANY_ARG "Too many arguments"
# define FAIL_INVALID_FILE "not a valid file"
# define FAIL_INVALID_OPT "not a valid option"
# define FAIL_ARG_CHECK "Argument check failed"
# define FAIL_GNL "GNL failed"
# define FAIL_PARS_ELEM "Parsing failed"
# define FAIL_PARS_MAP "Map parsing failed"
# define FAIL_INIT "Map initialisation has failed"
# define FAIL_BAD_CONF_FILE "Invalid configuration file"
# define FAIL_MALLOC "Malloc failed"
# define FAIL_MISSING_TEX_ID "one missing ID in g_id_texture (texture.c)"
# define FAIL_WRONG_DESCRIPTION_LINE "Wrong description line"
# define FAIL_RESOLUTION_PARS "Could not determine the resolution"
# define FAIL_WRONG_RESOLUTION "wrong resolution value(s)"
# define FAIL_COLOR_PARS "Could not determine the color"
# define FAIL_WRONG_RGB "wrong rgb values"
# define FAIL_MISSING_COLOR_ID "one missing ID in g_id_color (color.c)"
# define FAIL_COL_ALREADY_SET "this color has already been set"
# define FAIL_OTHER_1 "spaces and digits only after resolution ID please"
# define FAIL_OTHER_2 "nothing or spaces only after texture path please"
# define FAIL_OTHER_3 "nothing or spaces only after color description please"
# define FAIL_INVALID_MAP "Wrong map description line"
# define FAIL_TEXTURE_PARS "Could not determine the texture"
# define FAIL_TEXT_ALREADY_SET "this texture has already been set"
# define FAIL_RESOLUTION_ALREADY_SET "resolution has already been set"
# define FAIL_MISSING_PARS_ID "Missing ID in g_pars2 (mapping.c)"
# define FAIL_MAP_CHECK "Map checking failed"
# define FAIL_BREACH_FOUND "map is not closed, a breach has been found"
# define FAIL_MANY_POS "too many starting positions were found for the player"
# define FAIL_NO_POS "no starting position was found for the player"
# define FAIL_MIN_INFOS "Necessary information is missing"
# define FAIL_MISS_MAP "map is missing"
# define FAIL_MISS_TEX "one needed texture is missing"
# define FAIL_MISS_RES "image resolution is missing"
# define FAIL_MISS_COL_UP "roof color is missing"
# define FAIL_MISS_COL_GR "ground color is missing"
# define FAIL_NO_XPM "is not a .xpm file"
# define FAIL_NO_IMG "is not a valid image"
# define FAIL_SPRITE "Sprites parsing failed"
# define FAIL_SAVE "Saving the image failed"

# define ID_TEX_NO "NO"
# define ID_TEX_SO "SO"
# define ID_TEX_WE "WE"
# define ID_TEX_EA "EA"
# define ID_TEX_FL "FL"
# define ID_TEX_CL "CL"
# define ID_TEX_SP "S"
# define ID_TEX_TB "T"
# define ID_RES "R"
# define ID_COL_UP "C"
# define ID_COL_GR "F"
# define ID_POS_NORTH 'N'
# define ID_POS_EAST 'E'
# define ID_POS_WEST 'W'
# define ID_POS_SOUTH 'S'
# define ID_MAX_LEN 2

# define VACANT -1
# define WALL 1
# define SPRITE 2
# define TABLE 3
# define CEILING -2
# define FLOOR -3
# define MAP_MAX_VALUE 3

# define ACTIVE_RC true

# define ANGLE 0.66
# define MOVESPEED 0.2
# define ROT_SPEED 4.0

# define KEY_ESC 65307
# define KEY_ROT_L 65361
# define KEY_ROT_R 65363

# define KEY_LEFT 97
# define KEY_RIGHT 100
# define KEY_FRONT 119
# define KEY_BACK 115
/*
** AZERTY
**# define KEY_LEFT 113
**# define KEY_RIGHT 100
**# define KEY_FRONT 122
**# define KEY_BACK 115
*/

# define SAVE_NAME "save.bmp"

#endif
