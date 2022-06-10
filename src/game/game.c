/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:26:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 14:09:22 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <game/game.h>
#include <game/player.h>
#include <game/loop.h>
#include <config/config.h>
#include <config/map.h>
#include <config/parser.h>
#include <config/texture.h>
#include <graphics/window.h>
#include <graphics/image.h>

#include <utils/bool.h>
#include <utils/errors.h>
#include <strings.h>

void	game_destructor(t_game *game)
{
	if (game->window && game->config)
		config_destructor(game->window, game->config);
	if (game->window)
		window_destructor(game->window);
	if (game->player)
		player_destructor(game->player);
	*game = (t_game)
	{
		.config = NULL,
		.player = NULL,
		.window = NULL
	};
	free(game);
}

void	game_start_loop(t_game *game)
{
	game->window->img = image_constructor(game->window, NULL);
	game->window->buf_img = image_constructor(game->window, NULL);
	game->window->win = mlx_new_window(game->window->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_NAME);
	if (!game->window->win || !game->window->img || !game->window->buf_img)
		return ;
	game->window->open = TRUE;
	loop_start(game);
}

static t_bool	game_get_config(char *config_file_path, t_game *game)
{
	int		fd;
	t_bool	result;

	if (config_check_file_name(config_file_path))
	{
		fd = open(config_file_path, O_RDONLY);
		if (fd != -1)
		{
			result = parse_config_file(fd, game);
			close(fd);
			return (result);
		}
		else
			error_msg(strerror(errno), ADD_NO_NL);
	}
	else
		error_msg("Config file name is invalid", ADD);
	return (FALSE);
}

static t_game	*game_constructor(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		error_msg("Memory error: game_constructor", ADD);
		return (NULL);
	}
	game->window = window_constructor();
	game->config = config_constructor();
	if (!game->window || !game->config)
	{
		error_msg("Memory error: game_constructor", ADD);
		game_destructor(game);
		return (NULL);
	}
	return (game);
}

t_game	*game_init(char *config_file_path)
{
	t_game		*game;

	game = game_constructor();
	if (!game)
		return (NULL);
	if (game_get_config(config_file_path, game))
	{
		if (parse_map(game) && texture_open_images(game))
			return (game);
	}
	game_destructor(game);
	return (NULL);
}
