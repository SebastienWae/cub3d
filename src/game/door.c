/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:04 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/11 14:05:51 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>

void	door_toggle(t_game *game)
{
	int	colx;
	int	coly;

	colx = (int)(game->player->position.x + game->player->delta.x * 64) >> 6;
	coly = (int)(game->player->position.y + game->player->delta.y * 64) >> 6;
	if (game->config->map[coly][colx] == 'D')
	{
		game->config->map[coly][colx] = 'O';
		game->window->redraw = TRUE;
	}
	else if (game->config->map[coly][colx] == 'O')
	{
		game->config->map[coly][colx] = 'D';
		game->window->redraw = TRUE;
	}
}
