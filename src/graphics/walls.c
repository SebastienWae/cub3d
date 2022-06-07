/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 18:07:50 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/texture.h"
#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <utils/vec.h>

static void	walls_draw_slice(t_game *game, int x, double w, int wall_height, t_texture *texture)
{
	int		i;
	double	scale;
	int 	color;
	double	h_scale;
	int		zz = (WINDOW_HEIGHT - wall_height) / 1.5;

	scale = (double) wall_height / texture->height;
	// if (texture->height > texture->width)
		// h_scale = (int)(w * 5 /* *(double)texture->height / texture->width*/) % (texture->width);
	// else
	double pp = ((double)texture->width / 128);
	if (pp <= 0)
		pp = 1;
	h_scale =  (int)(w * pp) % (texture->width);
	i = 0;
	if (scale < 0.0001)
		scale = 1;
	while (i < wall_height && zz + i < WINDOW_HEIGHT)
	{
		color = image_get_pixel(texture->img, (t_vec){(int)h_scale, (int)(i / scale)}, texture->width, texture->height);
		if (zz + i > 0)
			image_put_pixel(game->window->img,
				(t_vec){
				x,
				zz + i,
			}, color);
		i ++;
	}
	/*while (i < wall_height)
	{
		draw_rectangle(game,
			(t_vec){x, (WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i},
			(t_vec){1, 1},
			image_get_pixel(texture->img,
				(t_vec)
			{
				(int)(w * 5) % (texture->width),
				(int)(i)
			},
				texture->width, texture->height));
		i ++;
	}*/
}

void	walls_draw_texture(t_game *game, t_ray *ray, int n, int wall_height)
{
	if (ray->type == HORIZONTAL
		&& ray->position.y < game->player->position.y)
		walls_draw_slice(game, n, ray->position.x,
			wall_height, game->config->textures[NORTH]);
	else if (ray->type == HORIZONTAL)
		walls_draw_slice(game, n, ray->position.x,
			wall_height, game->config->textures[SOUTH]);
	else if (ray->type == VERTICAL
		&& ray->position.x < game->player->position.x)
		walls_draw_slice(game, n, ray->position.y,
			wall_height, game->config->textures[WEST]);
	else if (ray->type == VERTICAL)
		walls_draw_slice(game, n, ray->position.y,
			wall_height, game->config->textures[EAST]);
}
