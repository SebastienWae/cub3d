/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:05:01 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 14:07:50 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/window.h>
#include <graphics/raycaster.h>

static void	rotate_left(t_game *game)
{
	if (game->player->direction > M_PI * 2)
		game->player->direction -= (M_PI * 2 + M_PI / 90);
	else
		game->player->direction += M_PI / 90;
}

static void	rotate_right(t_game *game)
{
	if (game->player->direction < 0)
		game->player->direction += (M_PI * 2 - M_PI / 90);
	else
		game->player->direction -= M_PI / 90;	
}

void	rotate(t_game *game, int keycode)
{
	if (keycode == KEY_LEFT)
		rotate_left(game);
	else if (keycode == KEY_RIGHT)
		rotate_right(game);
}
