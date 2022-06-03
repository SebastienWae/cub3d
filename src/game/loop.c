/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/06/03 07:41:46 by jenny            ###   ########.fr       */
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
	game->window->img = image_constructor(game->window);
	//draw_screen(game);
	//draw_mini_map(game);
	return (0);
}

static int	loop_keys_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		window_close(game->window);
	if (keycode == KEY_W)
	{	
		if (ray_caster(game, game->player->x, game->player->y, game->player->direction, 0xFF000000) > (int) (game->config->scale))
		{
			game->player->y -= (int)(game->config->scale / 5) * sin(game->player->direction);
			game->player->x += (int)(game->config->scale / 5) * cos(game->player->direction);
		}
	}
	if (keycode == KEY_S)
	{
		if (ray_caster(game, game->player->x, game->player->y, game->player->direction + M_PI, 0xFF000000) > (int) (game->config->scale / 2))
		{
		game->player->y += (int)(game->config->scale / 5) * sin(game->player->direction);
		game->player->x -= (int)(game->config->scale / 5) * cos(game->player->direction);
		}
	}
	if (keycode == KEY_A)
	{	
		if (ray_caster(game, game->player->x, game->player->y, game->player->direction + M_PI / 2, 0xFF000000) > (int) (game->config->scale / 2))
		{
		game->player->x -= (int)(game->config->scale / 5) * sin(game->player->direction);
		game->player->y -= (int)(game->config->scale / 5) * cos(game->player->direction);
		}
	}
	if (keycode == KEY_D)
	{	
		if (ray_caster(game, game->player->x, game->player->y, game->player->direction + 3 * M_PI / 2, 0xFF000000) > (int) (game->config->scale / 2))
		{
			game->player->x += (int)(game->config->scale / 5) * sin(game->player->direction);
			game->player->y += (int)(game->config->scale / 5) * cos(game->player->direction);
		}
	}
	if (keycode == KEY_LEFT)
	{		
		if (game->player->direction >= M_PI * 2)
			game->player->direction = game->player->direction - M_PI * 2 + M_PI / 90;
		else
			game->player->direction += M_PI / 90;
	}
	if (keycode == KEY_RIGHT)
	{
		if (game->player->direction <= 0)
			game->player->direction = game->player->direction + M_PI * 2 - M_PI / 90;
		else
			game->player->direction -= M_PI / 90;
	}
	draw_screen(game);
	draw_mini_map(game);
	return (0);
}

void	loop_start(t_game *game)
{	
	draw_screen(game);
	draw_mini_map(game);
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, 0, loop_keys_hook, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
