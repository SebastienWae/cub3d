/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 17:02:06 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <game/movements.h>
#include <graphics/walls.h>
#include <graphics/minimap.h>
#include <graphics/window.h>
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
		walls_draw(game);
		minimap_draw(game);
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->window->img->img, 0, 0);
		game->window->redraw = FALSE;
	}
	return (0);
}

static t_key_id	get_key_id(int keycode)
{
	if (keycode == KEY_LEFT)
		return (LEFT);
	else if (keycode == KEY_RIGHT)
		return (RIGHT);
	else if (keycode == KEY_W)
		return (W);
	else if (keycode == KEY_A)
		return (A);
	else if (keycode == KEY_S)
		return (S);
	else if (keycode == KEY_D)
		return (D);
	return (ERR_KEY);
}

static int	loop_keydown(int keycode, t_game *game)
{
	t_key_id	id;

	if (keycode == KEY_ESC)
		window_close(game->window);
	id = get_key_id(keycode);
	if (id != ERR_KEY)
		game->window->active_keys[id] = TRUE;
	return (0);
}

static int	loop_keyup(int keycode, t_game *game)
{
	t_key_id	id;

	if (keycode == KEY_ESC)
		window_close(game->window);
	id = get_key_id(keycode);
	if (id != ERR_KEY)
		game->window->active_keys[id] = FALSE;
	return (0);
}

void	loop_start(t_game *game)
{	
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, (1L << 0), loop_keydown, game);
	mlx_hook(game->window->win, ON_KEYUP, (1L << 1), loop_keyup, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
