/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:07:27 by seb               #+#    #+#             */
/*   Updated: 2022/06/06 13:20:56 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <math.h>
#include <config/config.h>
#include <game/game.h>

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

void	config_destructor(t_window *window, t_config *config)
{
	while (config->map_height--)
		free(config->map[(int)config->map_height]);
	free(config->map);
	if (config->textures[0])
		mlx_destroy_image(window->mlx, config->textures[0]);
	if (config->textures[1])
		mlx_destroy_image(window->mlx, config->textures[1]);
	if (config->textures[2])
		mlx_destroy_image(window->mlx, config->textures[2]);
	if (config->textures[3])
		mlx_destroy_image(window->mlx, config->textures[3]);
	*config = (t_config)
	{
		.map = NULL,
		.map_max_width = 0,
		.map_height = 0,
		.textures = {NULL, NULL, NULL, NULL},
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
	return (config);
}
