/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:39:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/05 14:24:46 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/bool.h"
#include <math.h>
#include <game/game.h>
#include <game/player.h>
#include <utils/vec.h>

void	move(t_game *game)
{
	int	ipx;
	int	ipy;

	ipx = game->player->position.x / 64.0;
	ipy = game->player->position.y / 64.0;
	if (game->window->active_keys[2] && !game->window->active_keys[4])
	{
		if (game->config->map[ipy][(int)((game->player->position.x + (game->player->delta.x * 16)) / 64.)] != '1')
			game->player->position.x += game->player->delta.x * 2;
		if (game->config->map[(int)((game->player->position.y + (game->player->delta.y * 16)) / 64.)][ipx] != '1')
			game->player->position.y += game->player->delta.y * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[4] && !game->window->active_keys[2])
	{
		if (game->config->map[ipy][(int)((game->player->position.x - (game->player->delta.x * 16)) / 64.)] != '1')
			game->player->position.x -= game->player->delta.x * 2;
		if (game->config->map[(int)((game->player->position.y - (game->player->delta.y * 16)) / 64.)][ipx] != '1')
			game->player->position.y -= game->player->delta.y * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[3] && !game->window->active_keys[5])
	{
		if (game->config->map[ipy]
			[(int)((game->player->position.x
					+ (game->player->delta.y * 16)) / 64.)] != '1')
			game->player->position.x += game->player->delta.y * 2;
		if (game->config->map
			[(int)((game->player->position.y - (game->player->delta.x * 16)) / 64.)]
			[ipx] != '1')
			game->player->position.y -= game->player->delta.x * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[5] && !game->window->active_keys[3])
	{
		if (game->config->map[ipy]
			[(int)((game->player->position.x
					- (game->player->delta.y * 16)) / 64.)] != '1')
			game->player->position.x -= game->player->delta.y * 2;
		if (game->config->map
			[(int)((game->player->position.y + (game->player->delta.x * 16)) / 64.)]
			[ipx] != '1')
			game->player->position.y += game->player->delta.x * 2;
		game->window->redraw = TRUE;
	}
}

void	rotate(t_game *game)
{
	if (game->window->active_keys[0] && !game->window->active_keys[1])
	{
		game->player->direction += 0.04;
		if (game->player->direction > M_PI * 2)
			game->player->direction -= M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[1] && !game->window->active_keys[0])
	{
		game->player->direction -= 0.04;
		if (game->player->direction < 0)
			game->player->direction += M_PI * 2;
		game->window->redraw = TRUE;
	}
	if (game->window->active_keys[0] || game->window->active_keys[1])
		game->player->delta = (t_vec){
			.x = cos(game->player->direction),
			.y = -sin(game->player->direction)};
}
