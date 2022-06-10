/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:37:54 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/10 11:38:01 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/image.h"
#include "graphics/color.h"
#include <math.h>
#include <graphics/render.h>
#include <graphics/walls.h>

static void	floor_draw(t_game *game)
{
	int	x;
	int	y;

	y = WINDOW_HEIGHT / 1.5;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			image_put_pixel(game->window, (t_vec){x, y},
				color_shade(game->config->colors[FLOOR],
					abs(y - WINDOW_HEIGHT) / 6));
			x++;
		}
		y++;
	}
}

static void	ceiling_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 1.5)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			image_put_pixel(game->window, (t_vec){x, y},
				color_shade(game->config->colors[CEILING],
					abs(y / 6)));
			x++;
		}
		y++;
	}
}

static void	walls_draw_wall(t_game *game, double ray_r, int n)
{
	t_ray	ray;
	double	fixed;

	ray = raycaster(game, ray_r);
	fixed = game->player->direction - ray_r;
	if (fixed > M_PI * 2)
		fixed -= M_PI * 2;
	else if (fixed < 0)
		fixed += M_PI * 2;
	ray.lenght *= cos(fixed);
	walls_draw_texture(game, &ray, n);
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
