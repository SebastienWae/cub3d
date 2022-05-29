/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:07:27 by seb               #+#    #+#             */
/*   Updated: 2022/05/29 13:23:05 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bool.h>
#include <errors.h>
#include <stdlib.h>
#include <window/window.h>
#include <strings/strings.h>
#include <config/config.h>
#include <config/map.h>
#include <config/texture.h>
#include <config/color.h>
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static t_bool	config_is_valid(t_config *config)
{
	if (config->map_width && config->map_height && config_map_is_valid(config)
		&& config->textures[NORTH] && config->textures[SOUTH]
		&& config->textures[EAST] && config->textures[WEST]
		&& config->colors[FLOOR] && config->colors[CEILING])
		return (TRUE);
	return (FALSE);
}

static void	config_error(t_config *config, t_window *window, int fd, char *line)
{
	config_destructor(window, config);
	window_destructor(window);
	close(fd);
	error_msg();
	ft_putstr_fd("Config file error at line: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

static void	config_parse_file(t_config *config, int fd, t_window *window)
{
	int				config_index;
	t_parser_state	state;
	char			*line;

	config_index = 0;
	state = CP_S_TEXTURES;
	line = get_next_line(fd);
	while (line && state != CP_S_DONE)
	{
		if (!line)
			state = CP_S_DONE;
		if (state == CP_S_TEXTURES)
			state = config_handle_texture(config, line, &config_index, window);
		else if (state == CP_S_COLORS)
			state = config_handle_color(config, line, &config_index);
		else
			state = config_handle_map(config, line, &config_index);
		if (state == CP_S_ERROR)
			config_error(config, window, fd, line);
		free(line);
		line = get_next_line(fd);
	}
}

t_config	*config_constructor(char *config_file_path, t_window *window)
{
	int			fd;
	t_config	*config;

	fd = open(config_file_path, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open config file");
	config = ft_calloc(1, sizeof(t_config));
	if (!config)
	{
		close(fd);
		return (NULL);
	}
	config->map_width = 0;
	config->map_height = 0;
	config_parse_file(config, fd, window);
	close(fd);
	if (config_is_valid(config))
		return (config);
	else
	{
		config_destructor(window, config);
		return (NULL);
	}
}

void	config_destructor(t_window *window, t_config *config)
{
	while (config->map_height--)
		free(config->map[config->map_height]);
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
		.map_width = 0,
		.map_height = 0,
		.textures = {NULL, NULL, NULL, NULL},
		.colors = {0, 0}
	};
	free(config);
}
