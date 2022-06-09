/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:16:03 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 10:45:34 by jeulliot         ###   ########.fr       */
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
	int	mouse_x;
	int	mouse_y;

	//linux
	//mlx_mouse_get_pos(game->window->mlx, game->window->win, &mouse_x, &mouse_y);
	// MAC
	mlx_mouse_get_pos(game->window->win, &mouse_x, &mouse_y);
	if (mouse_y > 0 && mouse_y < WINDOW_HEIGHT && mouse_x > 0 && mouse_x < WINDOW_WIDTH)
	{
		if (mouse_x < 4 * WINDOW_WIDTH / 9)
		{
			game->player->direction += fabs(mouse_x - (4 * (double)WINDOW_WIDTH / 9))/ 10000;
			if (game->player->direction > M_PI * 2)
				game->player->direction -= M_PI * 2;
			game->window->redraw = TRUE;
		}
		else if (mouse_x > 5 * WINDOW_WIDTH / 9)
		{
			game->player->direction -= (mouse_x - (5 * (double)WINDOW_WIDTH / 9)) / 10000;
			if (game->player->direction < 0)
				game->player->direction += M_PI * 2;
			game->window->redraw = TRUE;
		}
		game->player->delta = (t_vec){
			.x = cos(game->player->direction),
			.y = -sin(game->player->direction)};
	}
}

void	rotate(t_game *game)
{
	rotate_key(game);
	rotate_mouse(game);	
}
