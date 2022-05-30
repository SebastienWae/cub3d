/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/30 13:25:56 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <window/window.h>
#include <config/config.h>
#include <errors.h>

static void	destroy_game(t_game *game)
{
	config_destructor(game->window, game->config);
	window_destructor(game->window);
	*game = (t_game){NULL, NULL, NULL, NULL};
	free(game);
}

static t_game	*create_game(char *config_file_path)
{
	t_game		*game;
	t_window	*window;
	t_config	*config;

	window = window_constructor();
	if (!window)
		error_exit("Cannot create window");
	config = config_constructor(config_file_path, window);
	if (!config)
	{
		window_destructor(window);
		error_exit("Config file is not valid");
	}
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		config_destructor(window, config);
		window_destructor(window);
		error_exit("Memory error!");
	}
	*game = (t_game){config, window, NULL, NULL};
	return (game);
}

// TODO: remove
// FIXME: check game state first
static int	loop_hook(t_game *game)
{
	if (!game->window->open)
		destroy_game(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 1)
		error_exit("Missing path to the config file");
	else if (argc == 2)
	{
		game = create_game(argv[1]);
		mlx_loop_hook(game->window->mlx, loop_hook, game);
		mlx_loop(game->window->mlx);
	}
	else
		error_exit("Too many arguments");
}
