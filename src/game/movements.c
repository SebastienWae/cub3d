/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:39:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 15:05:04 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <game/player.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>

static void	move_up(t_game *game, t_vec vec)
{
	double	direction;

	direction = game->player->direction;
	if (raycaster(game, direction).distance > (game->config->scale))
	{
		game->player->position.x += vec.x;
		game->player->position.y -= vec.y;
	}
}

static void	move_down(t_game *game, t_vec vec)
{
	double	direction;

	direction = game->player->direction + M_PI;
	if (raycaster(game, direction).distance > (game->config->scale / 2))
	{
		game->player->position.x -= vec.x;
		game->player->position.y += vec.y;
	}
}

static void	move_left(t_game *game, t_vec vec)
{
	double	direction;

	direction = game->player->direction + M_PI / 2;
	if (raycaster(game, direction).distance > game->config->scale / 2)
	{
		game->player->position.x -= vec.y;
		game->player->position.y -= vec.x;
	}
}

static void	move_right(t_game *game, t_vec vec)
{
	double	direction;

	direction = game->player->direction + 3 * M_PI / 2;
	if (raycaster(game, direction).distance > (game->config->scale / 2))
	{
		game->player->position.x += vec.y;
		game->player->position.y += vec.x;
	}
}

void	move(t_game *game, int keycode)
{
	t_vec	vec;

	vec.y = (int)((game->config->scale / 5) * sin(game->player->direction));
	vec.x = (int)((game->config->scale / 5) * cos(game->player->direction));
	if (keycode == KEY_W)
		move_up(game, vec);
	else if (keycode == KEY_S)
		move_down(game, vec);
	else if (keycode == KEY_A)
		move_left(game, vec);
	else if (keycode == KEY_D)
		move_right(game, vec);
}
