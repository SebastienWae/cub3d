/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 21:28:26 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <game/game.h>
#include <graphics/image.h>
#include <graphics/window.h>
#include <graphics/draw.h>

static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		game_destructor(game);
		exit(EXIT_SUCCESS);
	}
	draw_mini_map(game);
	return (0);
}

static int	check_collision(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		if (game->config->map[(game->player->y + 2 * game->config->scale / 3)/game->config->scale - 1][(game->player->x + 1 * game->config->scale / 3)/game->config->scale] != '1'
		&& game->config->map[(game->player->y + 2 * game->config->scale / 3)/game->config->scale - 1][(game->player->x - 1 * game->config->scale / 3)/game->config->scale] != '1')
			return (0);
	if (keycode == KEY_S)
		if (game->config->map[(game->player->y - 2 * game->config->scale / 3)/game->config->scale + 1][(game->player->x + 1 * game->config->scale / 3)/game->config->scale] != '1'
		&& game->config->map[(game->player->y - 2 * game->config->scale / 3)/game->config->scale + 1][(game->player->x - 1 * game->config->scale / 3)/game->config->scale] != '1')
			return (0);
	if (keycode == KEY_A)
		if (game->config->map[(game->player->y + 1 * game->config->scale / 3)/game->config->scale][(game->player->x + 2 * game->config->scale / 3)/game->config->scale - 1] != '1'
		&& game->config->map[(game->player->y - 1 * game->config->scale / 3)/game->config->scale][(game->player->x + 2 * game->config->scale / 3)/game->config->scale - 1] != '1')
			return (0);
	if (keycode == KEY_D)
		if (game->config->map[(game->player->y - 1 * game->config->scale / 3)/game->config->scale][(game->player->x - 2 * game->config->scale / 3)/game->config->scale + 1] != '1'
		&& game->config->map[(game->player->y + 1 * game->config->scale / 3)/game->config->scale][(game->player->x - 2 * game->config->scale / 3)/game->config->scale + 1] != '1')
			return (0);
	return (1);
}

static int	loop_keys_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		window_close(game->window);
	if (keycode == KEY_W && !check_collision(keycode, game))		
		game->player->y--;
	if (keycode == KEY_S && !check_collision(keycode, game))
		game->player->y++;
	if (keycode == KEY_A && !check_collision(keycode, game))
		game->player->x--;
	if (keycode == KEY_D && !check_collision(keycode, game))
		game->player->x++;
	if (keycode == KEY_LEFT)
	{		
		if (game->player->direction == M_PI * 2)
			game->player->direction = M_PI / 90;
		else
			game->player->direction += M_PI / 90;
	}
	if (keycode == KEY_RIGHT)
	{
		if (game->player->direction == 0)
			game->player->direction = M_PI * 2 - M_PI / 90;
		else
			game->player->direction -= M_PI / 90;
	}
	return (0);
}

void	loop_start(t_game *game)
{
	draw_mini_map(game);
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, 0, loop_keys_hook, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
