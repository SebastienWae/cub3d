/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 14:01:34 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <utils/bool.h>
#include <utils/vec.h>

void	draw_rectangle(t_game *game, t_vec coord, t_vec size, int color)
{
	t_vec	i;

	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			image_put_pixel(game->window->img,
				(t_vec){(int)(coord.x + i.x), (int)(coord.y + i.y)}, color);
			i.x++;
		}
		i.y++;
	}
}

void	draw_ceiling(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, 0},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[CEILING]);
}

void	draw_floor(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, (int)(WINDOW_HEIGHT / 2)},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[FLOOR]);
}

void	draw_walls(t_game *game)
{
	int		w;
	t_ray	ray;
	double	ray_r;
	double	fixed;
	int		wall_height;

	w = 0;
	ray_r = game->player->direction + (M_PI / 6);
	while (w < WINDOW_WIDTH)
	{
		ray_r -= M_PI / 3. / WINDOW_WIDTH;
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
				(t_vec){w, (WINDOW_HEIGHT / 2) - (wall_height / 2)},
				(t_vec){1, wall_height}, 0x00505050);
		else
			draw_rectangle(game,
				(t_vec){w, (WINDOW_HEIGHT / 2) - (wall_height / 2)},
				(t_vec){1, wall_height}, 0x00454545);
		w++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	mapx;
	int	mapy;
	int	x;
	int	y;

	y = 0;
	while (y < 320)
	{
		x = 0;
		while (x < 320)
		{
			mapx = (int)(game->player->position.x + x - 160) >> 6;
			mapy = (int)(game->player->position.y + y - 160) >> 6;
			if (mapx < 0 || mapy < 0 || mapy > game->config->map_height - 1
				|| (size_t)mapx > ft_strlen(game->config->map[mapy]) - 1
				|| game->config->map[mapy][mapx] == ' ')
				draw_rectangle(game, (t_vec){x, y}, (t_vec){1, 1}, 0x00FFFFFF);
			else if (game->config->map[mapy][mapx] == '1')
				draw_rectangle(game, (t_vec){x, y}, (t_vec){1, 1}, 0x00404040);
			else
				draw_rectangle(game, (t_vec){x, y}, (t_vec){1, 1}, 0x00808080);
			x++;
		}
		y++;
	}
	draw_rectangle(game, (t_vec){156, 156}, (t_vec){8, 8}, 0x0000EEC2);
}
