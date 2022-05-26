/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:51:47 by seb               #+#    #+#             */
/*   Updated: 2022/05/26 22:07:23 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

typedef struct s_config		t_config;
typedef struct s_map		t_map;
typedef struct s_texture	t_texture;
typedef struct t_color		t_color;

enum	e_textures
{
	NORTH = 1,
	SOUTH,
	EAST,
	WEST
};

enum	e_colors
{
	FLOOR = 1,
	CEILING
};

struct	s_config
{
	t_map		*map;
	t_texture	*textures[4];
	t_color		*colors[2];
};

struct	s_map
{
	char	*map;
};

struct	s_textures
{
	char	*t;
};

struct	s_color
{
	char	*t;
};

t_config	*config_constructor(char *config_file_path);
void		config_destructor(t_config *config);

t_texture	*texture_constructor(char *texture_file_path);
void		texture_destructor(t_texture *texture);	

t_color		*color_constructor(char *rgb_color);
void		*color_destructor(t_color *color);

#endif
