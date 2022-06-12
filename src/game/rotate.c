/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:16:03 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 13:10:31 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/window.h>
#include <utils/bool.h>

static void	rotate_key(t_game *game)
{
	if (game->window->active_keys[0] && !game->window->active_keys[1])
	{
		game->player->direction += 0.02;
		if (game->player->direction > M_PI * 2)
			game->player->direction -= M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[1] && !game->window->active_keys[0])
	{
		game->player->direction -= 0.02;
		if (game->player->direction < 0)
			game->player->direction += M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[0] || game->window->active_keys[1])
		game->player->delta = (t_vec){
			.x = cos(game->player->direction),
			.y = -sin(game->player->direction)};
}

static void	rotate_mouse(t_game *game)
{
	int	mx;
	int	my;

	mlx_mouse_get_pos(game->window->win, &mx, &my);
	if (my > 0 && my < WINDOW_HEIGHT && mx > 0 && mx < WINDOW_WIDTH)
	{
		if (mx < 4 * WINDOW_WIDTH / 9)
		{
			game->player->direction += fabs(mx
					- (4 * (double)WINDOW_WIDTH / 9)) / 20000;
			if (game->player->direction > M_PI * 2)
				game->player->direction -= M_PI * 2;
			game->window->redraw = TRUE;
		}
		else if (mx > 5 * WINDOW_WIDTH / 9)
		{
			game->player->direction -= (mx
					- (5 * (double)WINDOW_WIDTH / 9)) / 20000;
			if (game->player->direction < 0)
				game->player->direction += M_PI * 2;
			game->window->redraw = TRUE;
		}
		game->player->delta = (t_vec){
			cos(game->player->direction), -sin(game->player->direction)};
	}
}

void	rotate(t_game *game)
{
	rotate_key(game);
	rotate_mouse(game);
}
