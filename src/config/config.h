/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:51:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 13:34:43 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <graphics/window.h> 

enum	e_door_textures
{
	DOOR_OPEN,
	DOOR_CLOSE
};

enum	e_textures
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	ARROW
};

enum	e_colors
{
	FLOOR,
	CEILING
};

typedef struct s_config
{
	char	**map;
	double	map_height;
	double	map_width;
	void	*walls_txt[5];
	void	*doors_txt[2];
	void	*player_txt;
	int		colors[2];
}	t_config;

t_config	*config_constructor(void);
void		config_destructor(t_window *window, t_config *config);
t_bool		config_check_file_name(char *config_file_path);

#endif
