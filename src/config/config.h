/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:51:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/04 16:28:19 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>
# include <graphics/window.h> 

enum	e_textures
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum	e_colors
{
	FLOOR,
	CEILING
};

typedef struct s_config
{
	char	**map;
	double	map_max_width;
	double	map_height;
	void	*textures[4];
	int		colors[2];
}	t_config;

t_config	*config_constructor(void);
void		config_destructor(t_window *window, t_config *config);

#endif
