/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 16:40:29 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <utils/vec.h>

static void	ceiling_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, 0},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[CEILING]);
}

static void	floor_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, (int)(WINDOW_HEIGHT / 2)},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[FLOOR]);
}

static void	walls_draw_wall(t_game *game, double ray_r, int n)
{
	t_ray	ray;
	double	fixed;
	int		wall_height;

	ray = raycaster(game, ray_r);
	fixed = game->player->direction - ray_r;
	if (fixed > M_PI * 2)
		fixed -= M_PI * 2;
	else if (fixed < 0)
		fixed += M_PI * 2;
	ray.lenght *= cos(fixed);
	wall_height = (64 * 320) / ray.lenght;
	if (ray.type == HORIZONTAL)
		draw_rectangle(game,
			(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
			(t_vec){1, wall_height}, 0x00505050);
	else
		draw_rectangle(game,
			(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
			(t_vec){1, wall_height}, 0x00454545);
}

void	walls_draw(t_game *game)
{
	int		w;
	double	ray_r;

	ceiling_draw(game);
	floor_draw(game);
	w = 0;
	ray_r = game->player->direction + (M_PI / 6);
	while (w < WINDOW_WIDTH)
	{
		ray_r -= M_PI / 3. / WINDOW_WIDTH;
		walls_draw_wall(game, ray_r, w);
		w++;
	}
}
