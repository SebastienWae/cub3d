/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:37:54 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/11 15:34:46 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/window.h>
#include <graphics/image.h>
#include <graphics/color.h>
#include <graphics/walls.h>
#include <graphics/minimap.h>

static void	floor_draw(t_game *game)
{
	int				x;
	int				y;
	unsigned int	color;

	y = WINDOW_HEIGHT >> 1;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = color_shade(game->config->colors[FLOOR],
					abs(y - WINDOW_HEIGHT) / 6);
			image_put_pixel(game->window, (t_vec){x, y}, color);
			x++;
		}
		y++;
	}
}

static void	ceiling_draw(t_game *game)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < WINDOW_HEIGHT >> 1)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = color_shade(game->config->colors[CEILING], abs(y / 6));
			image_put_pixel(game->window, (t_vec){x, y}, color);
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
	while (w < WINDOW_WIDTH)
	{
		walls_draw_wall(game, ray_r, w);
		ray_r = game->player->direction - atan((w - ((double)WINDOW_WIDTH / 2))
				/ (((double)WINDOW_WIDTH / 2) / tan(M_PI / 6.)));
		w++;
	}
	minimap_draw(game);
}
