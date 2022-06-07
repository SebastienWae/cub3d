/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:20:17 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 15:11:01 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>

//FIXME: delete this junk
 void	minimap_draw_player(t_game *game)
{
	t_ray	ray;
	t_vec	d;
	int		w;
	double	ray_r;
	double	y;

	w = 0;
	ray_r = game->player->direction + (M_PI / 6);
	while (w < WINDOW_WIDTH)
	{
		ray_r -= M_PI / 3. / WINDOW_WIDTH;
		ray = raycaster(game, ray_r);
		d = (t_vec)
		{
			.x = ray.position.x - game->player->position.x,
			.y = ray.position.y - game->player->position.y
		};
		if (d.x > 0)
		{
			y = 160.;
			for (int x = 0; x < d.x; x++)
			{
				y += d.y / d.x;
				image_put_pixel(game->window->img, (t_vec){(int)(x + 160), (int)y}, 0x00FF0000);
			}
		}
		else
		{
			y = 160.;
			for (int x = 0; x > d.x; x--)
			{
				y += d.y / -d.x;
				image_put_pixel(game->window->img, (t_vec){(int)(x + 160), (int)y}, 0x00FF0000);
			}
		}
		w++;
	}
}

static void	minimap_draw_elem(t_game *game, int x, int y)
{
	int	mapx;
	int	mapy;

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
}

void	minimap_draw(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 320)
	{
		x = 0;
		while (x < 320)
		{
			minimap_draw_elem(game, x, y);
			x++;
		}
		y++;
	}
	draw_rectangle(game, (t_vec){156, 156}, (t_vec){4, 4}, 0x0000EEC2);
	minimap_draw_player(game);
}
