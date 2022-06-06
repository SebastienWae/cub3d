/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:16:03 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 16:16:53 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/window.h>
#include <utils/bool.h>

void	rotate(t_game *game)
{
	if (game->window->active_keys[0] && !game->window->active_keys[1])
	{
		game->player->direction += 0.08;
		if (game->player->direction > M_PI * 2)
			game->player->direction -= M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[1] && !game->window->active_keys[0])
	{
		game->player->direction -= 0.08;
		if (game->player->direction < 0)
			game->player->direction += M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[0] || game->window->active_keys[1])
		game->player->delta = (t_vec){
			.x = cos(game->player->direction),
			.y = -sin(game->player->direction)};
}
