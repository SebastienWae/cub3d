/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:37:54 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/07 11:43:10 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <graphics/draw.h>
#include <graphics/render.h>
#include <graphics/walls.h>

static void	floor_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, (int)(WINDOW_HEIGHT / 2)},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[FLOOR]);
}

static void	ceiling_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, 0},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[CEILING]);
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
	walls_draw_texture(game, &ray, n, wall_height);
}

void	render(t_game *game)
{
	int		w;
	double	ray_r;

	ceiling_draw(game);
	floor_draw(game);
	w = 0;
	ray_r = game->player->direction + (M_PI / 6);
	if (ray_r > M_PI * 2)
		ray_r -= M_PI * 2;
	while (w < WINDOW_WIDTH)
	{		
		walls_draw_wall(game, ray_r, w);
		ray_r -= M_PI / 3. / WINDOW_WIDTH;
		if (ray_r < 0)
			ray_r += M_PI * 2;
		w++;
	}
}