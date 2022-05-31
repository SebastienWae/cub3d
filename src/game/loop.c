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

#include <game/game.h>
#include <graphics/window.h>

static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		game_destructor(game);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

static int	loop_keys_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		window_close(game->window);
	return (0);
}

void	loop_start(t_game *game)
{
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_key_hook(game->window->win, loop_keys_hook, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
