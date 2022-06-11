/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:20:17 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 14:03:26 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <game/game.h>
#include <config/texture.h>
#include <graphics/image.h>
#include <utils/vec.h>

static t_vec	minimap_get_pixel(t_game *game, t_texture *texture, t_vec pos)
{	
	t_vec	coord;
	double	cos_a;
	double	sin_a;

	cos_a = cos (-game->player->direction);
	sin_a = sin(-game->player->direction);
	coord = (t_vec)
	{
		(int)((double)texture->width / 2
			+ ((int)pos.x - (double)texture->width / 2) * cos_a
			+ ((int)pos.y - (double)texture->height / 2) * sin_a),
		(int)((double)texture->height / 2
			+ ((int)pos.y - (double)texture->height / 2) * cos_a
			- ((int)pos.x - (double)texture->width / 2) * sin_a)
	};
	return (coord);
}

static void	minimap_rotate_arrow(t_game *game, t_texture *texture)
{
	double	x;
	double	y;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{		
			image_put_pixel(game->window,
				(t_vec)
			{
				160 + (int)x - (double)texture->width / 2,
				160 + (int)y - (double)texture->height / 2
			},
				image_get_pixel(texture->img,
					minimap_get_pixel(game, texture, (t_vec){x, y}),
					texture->width, texture->height));
			x++;
		}
		y++;
	}
}

static void	minimap_frame(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 320)
	{
		x = 0;
		while (x < 4)
		{
			image_put_pixel(game->window, (t_vec){x, y}, 0x00000000);
			x ++;
		}
		while (x < 316)
		{
			if ((y >= 0 && y < 4) || y >= 316)
				image_put_pixel(game->window, (t_vec){x, y}, 0x00000000);
			x ++;
		}
		while (x < 320)
		{
			image_put_pixel(game->window, (t_vec){x, y}, 0x00000000);
			x ++;
		}
		y++;
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
		image_draw_rectangle(game->window,
			(t_vec){x, y}, (t_vec){4, 4}, 0x00404040);
	else if (game->config->map[mapy][mapx] == '1')
		image_draw_rectangle(game->window,
			(t_vec){x, y}, (t_vec){4, 4}, 0x00404040);
	else if (game->config->map[mapy][mapx] == 'D')
		image_draw_rectangle(game->window,
			(t_vec){x, y}, (t_vec){4, 4}, 0x00606060);
	else
		image_draw_rectangle(game->window,
			(t_vec){x, y}, (t_vec){4, 4}, 0x00808080);
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
			x += 4;
		}
		y += 4;
	}
	minimap_rotate_arrow(game, game->config->player_txt);
	minimap_frame(game);
}
