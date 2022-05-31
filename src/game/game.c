/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 08:26:49 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 11:59:39 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft.h>
#include <game/game.h>
#include <game/player.h>
#include <game/loop.h>
#include <config/config.h>
#include <config/parser.h>
#include <graphics/window.h>
#include <graphics/image.h>

void	game_destructor(t_game *game)
{
	if (game->window && game->config)
		config_destructor(game->window, game->config);
	if (game->window)
		window_destructor(game->window);
	if (game->player)
		player_destructor(game->player);
	if (game->doors)
		free(game->doors); // TODO: call destructor
	free(game);
}

t_game	*game_constructor(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->window = window_constructor();
	game->config = config_constructor();
	game->player = player_constructor();
	if (!game->window || !game->config || !game->player)
	{
		game_destructor(game);
		return (NULL);
	}
	return (game);
}

static void	game_get_config(char *config_file_path, t_game *game)
{
	int	fd;

	fd = open(config_file_path, O_RDONLY);
	if (fd == -1)
	{
		config_destructor(game->window, game->config);
		game->config = NULL;
		player_destructor(game->player);
		game->player = NULL;
		return ;
	}
	if (!parse_config_file(fd, game))
	{
		config_destructor(game->window, game->config);
		game->config = NULL;
		player_destructor(game->player);
		game->player = NULL;
	}
	config_set_scale(game);
	close(fd);
}

void	game_start_loop(t_game *game)
{
	game->window->img = image_constructor(game->window);
	game->window->win = mlx_new_window(game->window->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_NAME);
	if (!game->window->win || !game->window->img)
		return ;
	game->window->open = TRUE;
	loop_start(game);
}

t_game	*game_init(char *config_file_path)
{
	t_game		*game;

	game = game_constructor();
	if (!game)
		return (NULL);
	game_get_config(config_file_path, game);
	if (!game->config || !game->player)
	{
		game_destructor(game);
		return (NULL);
	}
	if (!parse_map(game))
	{
		game_destructor(game);
		return (NULL);
	}
	return (game);
}