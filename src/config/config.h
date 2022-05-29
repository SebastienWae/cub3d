/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:51:47 by seb               #+#    #+#             */
/*   Updated: 2022/05/29 13:22:13 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>
# include <window/window.h> 

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

typedef enum e_parser_state
{
	CP_S_TEXTURES,
	CP_S_COLORS,
	CP_S_MAP,
	CP_S_DONE,
	CP_S_ERROR
}	t_parser_state;

typedef struct s_config
{
	char	**map;
	size_t	map_width;
	size_t	map_height;
	void	*textures[4];
	int		colors[2];
}	t_config;

t_config		*config_constructor(char *config_file_path, t_window *window);
void			config_destructor(t_window *window, t_config *config);

#endif
