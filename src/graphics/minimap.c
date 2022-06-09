/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:20:17 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 16:28:15 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <math.h>
#include <config/texture.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>

static void minimap_rotate_arrow(t_game *game, t_texture *texture)
{
	double	x;
	double	y;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x< texture->width)
		{		
		image_put_pixel(game->window->img, (t_vec){160 + (int)x - (double)texture->width/2, 160 + (int)y - (double)texture->height/2}, 
				image_get_pixel(texture->img, 
			(t_vec){
				(int)((double)texture->width/2 + ((int)x - (double)texture->width/2) * cos (-game->player->direction) + (int)((int)y - (double)texture->height/2) * sin(-game->player->direction)), 
				(int)((double)texture->height/2 + (int)((int)y - (double)texture->height/2) * cos (-game->player->direction) - ((int)x - (double)texture->width/2) * sin(-game->player->direction))
				}, 
			texture->width, texture->height));
		x ++;
		}
	y ++;
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
		return ;
	else if (game->config->map[mapy][mapx] == '1')
		draw_rectangle(game, (t_vec){x, y}, (t_vec){4, 4}, 0x00404040);
	else if (game->config->map[mapy][mapx] == 'D')
		draw_rectangle(game, (t_vec){x, y}, (t_vec){4, 4}, 0x00606060);
	else
		draw_rectangle(game, (t_vec){x, y}, (t_vec){4, 4}, 0x00808080);
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
	minimap_rotate_arrow(game, game->config->textures[ARROW]);
}
