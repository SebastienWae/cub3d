/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 14:17:07 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <game/movements.h>
#include <graphics/draw.h>
#include <utils/bool.h>

static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		game_destructor(game);
		exit(EXIT_SUCCESS);
	}
	rotate(game);
	move(game);
	if (game->window->redraw)
	{
		draw_floor(game);
		draw_ceiling(game);
		draw_walls(game);
		draw_mini_map(game);
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->window->img->img, 0, 0);
		game->window->redraw = FALSE;
	}
	return (0);
}

static int	get_key_id(int keycode)
{
	if (keycode == KEY_LEFT)
		return (0);
	else if (keycode == KEY_RIGHT)
		return (1);
	else if (keycode == KEY_W)
		return (2);
	else if (keycode == KEY_A)
		return (3);
	else if (keycode == KEY_S)
		return (4);
	else if (keycode == KEY_D)
		return (5);
	return (-1);
}

static int	loop_keydown(int keycode, t_game *game)
{
	int	id;

	if (keycode == KEY_ESC)
		window_close(game->window);
	id = get_key_id(keycode);
	if (id != -1)
		game->window->active_keys[id] = TRUE;
	return (0);
}

static int	loop_keyup(int keycode, t_game *game)
{
	int	id;

	if (keycode == KEY_ESC)
		window_close(game->window);
	id = get_key_id(keycode);
	if (id != -1)
		game->window->active_keys[id] = FALSE;
	return (0);
}

void	loop_start(t_game *game)
{	
	draw_mini_map(game);
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, (1L << 0), loop_keydown, game);
	mlx_hook(game->window->win, ON_KEYUP, (1L << 1), loop_keyup, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
