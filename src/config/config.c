/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:07:27 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 15:43:17 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <game/game.h>
#include <graphics/image.h>
#include <config/texture.h>
#include <utils/bool.h>

t_bool	config_check_file_name(char *config_file_path)
{
	int	len;

	len = ft_strlen(config_file_path);
	if (len < 4)
		return (FALSE);
	if (ft_strncmp(config_file_path + (len - 4), ".cub", 5))
		return (FALSE);
	return (TRUE);
}

void	config_wall_destructor(t_config *config, t_window *window)
{
	if (config->walls_txt[0])
	{
		image_destructor(window, ((t_texture *)(config->walls_txt[0]))->img);
		free(config->walls_txt[0]);
	}
	if (config->walls_txt[1])
	{
		image_destructor(window, ((t_texture *)(config->walls_txt[1]))->img);
		free(config->walls_txt[1]);
	}
	if (config->walls_txt[2])
	{
		image_destructor(window, ((t_texture *)(config->walls_txt[2]))->img);
		free(config->walls_txt[2]);
	}
	if (config->walls_txt[3])
	{
		image_destructor(window, ((t_texture *)(config->walls_txt[3]))->img);
		free(config->walls_txt[3]);
	}
}

static void	config_texture_destructor(t_config *config, t_window *window)
{
	if (config->doors_txt[0])
	{
		image_destructor(window, ((t_texture *)(config->doors_txt[0]))->img);
		free(config->doors_txt[0]);
	}
	if (config->doors_txt[1])
	{
		image_destructor(window, ((t_texture *)(config->doors_txt[1]))->img);
		free(config->doors_txt[1]);
	}
	if (config->player_txt)
	{
		image_destructor(window, ((t_texture *)(config->player_txt))->img);
		free(config->player_txt);
	}
}

void	config_destructor(t_window *window, t_config *config)
{
	while (config->map_height--)
		free(config->map[(int)config->map_height]);
	free(config->map);
	config_wall_destructor(config, window);
	config_texture_destructor(config, window);
	*config = (t_config)
	{
		.map = NULL,
		.map_width = 0,
		.map_height = 0,
		.walls_txt = {NULL, NULL, NULL, NULL},
		.doors_txt = {NULL, NULL},
		.player_txt = NULL,
		.colors = {0, 0}
	};
	free(config);
}

t_config	*config_constructor(void)
{
	t_config	*config;

	config = ft_calloc(1, sizeof(t_config));
	if (!config)
		return (NULL);
	config->walls_txt[0] = NULL;
	config->walls_txt[1] = NULL;
	config->walls_txt[2] = NULL;
	config->walls_txt[3] = NULL;
	config->doors_txt[0] = NULL;
	config->doors_txt[1] = NULL;
	return (config);
}
