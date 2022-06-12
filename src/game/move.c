/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:39:53 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 13:11:38 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <game/player.h>
#include <graphics/window.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>
#include <utils/bool.h>

static t_vec	move_up(t_game *game, t_vec new_pos)
{
	int		colx;
	int		coly;
	int		mapx;
	int		mapy;
	t_ray	ray;

	ray = raycaster(game, game->player->direction);
	mapx = (int)game->player->position.x >> 6;
	mapy = (int)game->player->position.y >> 6;
	colx = (int)(new_pos.x + game->player->delta.x * 32) >> 6;
	coly = (int)(new_pos.y + game->player->delta.y * 32) >> 6;
	if (game->config->map[mapy][colx] != '1'
		&& game->config->map[mapy][colx] != 'D'
		&& ray.lenght > 32)
		new_pos.x += game->player->delta.x * 2;
	if (game->config->map[coly][mapx] != '1'
		&& game->config->map[coly][mapx] != 'D'
		&& ray.lenght > 32)
		new_pos.y += game->player->delta.y * 2;
	return (new_pos);
}

static t_vec	move_down(t_game *game, t_vec new_pos)
{
	int		colx;
	int		coly;
	int		mapx;
	int		mapy;
	t_ray	ray;

	ray = raycaster(game, game->player->direction + M_PI);
	mapx = (int)game->player->position.x >> 6;
	mapy = (int)game->player->position.y >> 6;
	colx = (int)(new_pos.x - game->player->delta.x * 16) >> 6;
	coly = (int)(new_pos.y - game->player->delta.y * 16) >> 6;
	if (game->config->map[mapy][colx] != '1'
		&& game->config->map[mapy][colx] != 'D'
		&& ray.lenght > 32)
		new_pos.x -= game->player->delta.x * 2;
	if (game->config->map[coly][mapx] != '1'
		&& game->config->map[coly][mapx] != 'D'
		&& ray.lenght > 32)
		new_pos.y -= game->player->delta.y * 2;
	return (new_pos);
}

static t_vec	move_left(t_game *game, t_vec new_pos)
{
	int		colx;
	int		coly;
	int		mapx;
	int		mapy;
	t_ray	ray;

	ray = raycaster(game, game->player->direction + M_2_PI);
	mapx = (int)game->player->position.x >> 6;
	mapy = (int)game->player->position.y >> 6;
	colx = (int)(new_pos.x + game->player->delta.y * 16) >> 6;
	coly = (int)(new_pos.y - game->player->delta.x * 16) >> 6;
	if (game->config->map[mapy][colx] != '1'
		&& game->config->map[mapy][colx] != 'D'
		&& ray.lenght > 32)
		new_pos.x += game->player->delta.y * 2;
	if (game->config->map[coly][mapx] != '1'
		&& game->config->map[coly][mapx] != 'D'
		&& ray.lenght > 32)
		new_pos.y -= game->player->delta.x * 2;
	return (new_pos);
}

static t_vec	move_right(t_game *game, t_vec new_pos)
{
	int		colx;
	int		coly;
	int		mapx;
	int		mapy;
	t_ray	ray;

	ray = raycaster(game, game->player->direction - M_2_PI);
	mapx = (int)game->player->position.x >> 6;
	mapy = (int)game->player->position.y >> 6;
	colx = (int)(new_pos.x - game->player->delta.y * 16) >> 6;
	coly = (int)(new_pos.y + game->player->delta.x * 16) >> 6;
	if (game->config->map[mapy][colx] != '1'
		&& game->config->map[mapy][colx] != 'D'
		&& ray.lenght > 32)
		new_pos.x -= game->player->delta.y * 2;
	if (game->config->map[coly][mapx] != '1'
		&& game->config->map[coly][mapx] != 'D'
		&& ray.lenght > 32)
		new_pos.y += game->player->delta.x * 2;
	return (new_pos);
}

void	move(t_game *game)
{
	t_vec	new_position;

	if (game->window->active_keys[W] || game->window->active_keys[S]
		|| game->window->active_keys[A] || game->window->active_keys[D])
	{
		new_position = game->player->position;
		if (game->window->active_keys[W])
			new_position = move_up(game, new_position);
		if (game->window->active_keys[S])
			new_position = move_down(game, new_position);
		if (game->window->active_keys[A])
			new_position = move_left(game, new_position);
		if (game->window->active_keys[D])
			new_position = move_right(game, new_position);
		game->player->position = new_position;
		game->window->redraw = TRUE;
	}
}
