/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 12:08:38 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/image.h"
#include <game/game.h>
#include <graphics/window.h>
#include <math.h>
#include <stddef.h>

void	draw_ray(t_game *game, size_t x, size_t y, double direction, int color)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while (y + j > 0 && y + j < WINDOW_HEIGHT && x + i > 0 && x + i < WINDOW_WIDTH)
	{
		image_put_pixel(game->window->img, x + i, y + j, color);
		i = i + cos(direction);
		j = j - sin(direction);
	}
}

void	draw_rectangle(t_game *game, size_t x, size_t y, size_t size_x, size_t size_y, int color)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			image_put_pixel(game->window->img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void	draw_player(t_game *game)
{	
	draw_rectangle(game, game->player->x - game->config->scale / 6,
		game->player->y - game->config->scale / 6,
		game->config->scale / 3, game->config->scale / 3, 0x0000EEC2);
	draw_ray(game, game->player->x, game->player->y,
		game->player->direction, 0x0000EEC2);
}

void	draw_mini_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < ft_strlen(game->config->map[y]))
		{
			if (game->config->map[y][x] == '1')
				draw_rectangle(game, game->config->scale * x,
					game->config->scale * y, game->config->scale,
					game->config->scale, 0x00404040);
			else if (game->config->map[y][x] == '0'
					|| game->config->map[y][x] == 'N'
					|| game->config->map[y][x] == 'E'
					|| game->config->map[y][x] == 'S'
					|| game->config->map[y][x] == 'W')
				draw_rectangle(game, game->config->scale * x,
					game->config->scale * y, game->config->scale,
					game->config->scale, 0x00808080);
			x++;
		}
		y++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->window->mlx, game->window->win, game->window->img->img, 0, 0);
}

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

static int	loop_keys_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		window_close(game->window);
	if (keycode == KEY_W)
		game->player->y--;
	if (keycode == KEY_S)
		game->player->y++;
	if (keycode == KEY_A)
		game->player->x--;
	if (keycode == KEY_D)
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
