/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 15:41:43 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <graphics/color.h>
#include <config/texture.h>
#include <utils/vec.h>

static void	walls_draw_slice(t_game *game, int x, double w, t_ray *ray, int wall_height, t_texture *texture)
{	
	int		i;
	int		zz;
	int		color;
	t_vec	scale;
	double	pp;

	scale.y = (double) wall_height / texture->height;
	pp = ((double)texture->width / 64);
	zz = (WINDOW_HEIGHT - wall_height) / 1.5;
	if (pp <= 0)
		pp = 1;
	scale.x = (int)(w * pp) % (texture->width);
	i = 0;
	if (scale.y < 0.0001)
		scale.y = 1;
	while (i < wall_height && zz + i < WINDOW_HEIGHT)
	{
		color = image_get_pixel(texture->img,
				(t_vec){(int)scale.x, (int)(i / scale.y)},
				texture->width, texture->height);
		color = color_shade(color, ray->lenght / 3);
		if (zz + i > 0)
			image_put_pixel(game->window->img,
				(t_vec){
				x,
				zz + i,
			}, color);
		i ++;
	}
}

void	walls_draw_texture(t_game *game, t_ray *ray, int n, int wall_height)
{
	if (ray->texture == T_DOOR_OPEN || ray->texture == T_DOOR_CLOSE)
	{
		if (ray->type == HORIZONTAL)
			walls_draw_slice(game, n, ray->position.x, ray,
				wall_height, game->config->textures[ray->texture]);
		else if (ray->type == VERTICAL)
			walls_draw_slice(game, n, ray->position.y, ray,
				wall_height, game->config->textures[ray->texture]);
	}
	else
	{
		if (ray->type == HORIZONTAL
			&& ray->position.y < game->player->position.y)
			walls_draw_slice(game, n, ray->position.x, ray,
				wall_height, game->config->textures[NORTH]);
		else if (ray->type == HORIZONTAL)
			walls_draw_slice(game, n, ray->position.x, ray,
				wall_height, game->config->textures[SOUTH]);
		else if (ray->type == VERTICAL
			&& ray->position.x < game->player->position.x)
			walls_draw_slice(game, n, ray->position.y, ray,
				wall_height, game->config->textures[WEST]);
		else if (ray->type == VERTICAL)
			walls_draw_slice(game, n, ray->position.y, ray,
				wall_height, game->config->textures[EAST]);
	}
}
