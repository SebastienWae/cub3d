/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/06/04 16:10:38 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <game/movements.h>
#include <game/rotation.h>
#include <graphics/draw.h>
#include <utils/bool.h>

static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		game_destructor(game);
		exit(EXIT_SUCCESS);
	}
	if (game->window->redraw)
	{
		draw_screen(game);
		draw_mini_map(game);
		mlx_put_image_to_window(game->window->mlx, game->window->win, game->window->img->img, 0, 0);
		game->window->redraw = FALSE;
	}
	return (0);
}

static int	loop_keys_hook(int keycode, t_game *game)
{
	mlx_put_image_to_window(game->window->mlx, game->window->win, game->window->img->img, 0, 0);
	if (keycode == KEY_ESC)
		window_close(game->window);
	if (keycode == KEY_W
		|| keycode == KEY_S
		|| keycode == KEY_A
		|| keycode == KEY_D)
		move(game, keycode);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate(game, keycode);
	game->window->redraw = TRUE;
	return (0);
}

void	loop_start(t_game *game)
{	
	draw_screen(game);
	draw_mini_map(game);
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, (1L << 0), loop_keys_hook, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
