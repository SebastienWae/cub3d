/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:05:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/30 16:00:22 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <cub3d.h>
#include <stddef.h>
#include <stdlib.h>
#include <graphics/window.h>
#include <graphics/image.h>
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
static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		destroy_game(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

#include <stdio.h>
void	draw_map(t_game *game)
{
	t_coordonate	pixel;
	size_t			width;
	size_t			height;
	size_t			x;
	size_t			y;

	pixel.y = 0;
	width = WINDOW_WIDTH / game->config->map_width - 1;
	height = WINDOW_HEIGHT / game->config->map_height - 1;
	while (pixel.y < WINDOW_HEIGHT)
	{
		pixel.x = 0;
		y = pixel.y / height;
		if (y < game->config->map_height)
		{
			while (pixel.x < WINDOW_WIDTH)
			{
				x = pixel.x / width;
				if (x < ft_strlen(game->config->map[y]))
				{
					if (game->config->map[y][x] == '1')
						image_put_pixel(game->window->img, pixel.x, pixel.y, 0x00FF0000);
					else if (game->config->map[y][x] == 'N')
						image_put_pixel(game->window->img, pixel.x, pixel.y, 0x0000FF00);
				}
				pixel.x++;
			}
		}
		pixel.y++;
	}
	mlx_put_image_to_window(game->window->mlx, game->window->win,
		game->window->img->img, 0, 0);
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
		draw_map(game);
		mlx_loop(game->window->mlx);
	}
	else
		error_exit("Too many arguments");
}
