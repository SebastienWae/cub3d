/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:53:59 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 14:09:32 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <config/texture.h>
#include <graphics/color.h>
#include <graphics/image.h>
#include <graphics/window.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>

static	t_vec	walls_get_scale(t_ray *ray, t_texture *t, int height)
{
	t_vec	scale;
	double	block_width;

	block_width = ((double)t->width / 64);
	if (block_width <= 0)
		block_width = 1;
	if (ray->type == HORIZONTAL)
		scale.x = (int)(ray->pos.x * block_width) % (t->width);
	else
		scale.x = (int)(ray->pos.y * block_width) % (t->width);
	scale.y = (double)height / t->height;
	if (scale.y < 0.0001)
		scale.y = 1;
	return (scale);
}

static void	walls_draw_slice(t_game *game, int n, t_ray *ray, t_texture *t)
{	
	int				i;
	t_vec			scale;
	int				height;
	unsigned int	color;
	int				zz;

	height = (64 * WINDOW_WIDTH) / ray->lenght;
	scale = walls_get_scale(ray, t, height);
	i = 0;
	zz = (WINDOW_HEIGHT - height) >> 1;
	while (i < height && zz + i < WINDOW_HEIGHT)
	{
		color = image_get_pixel(t->img, (t_vec){(int)scale.x,
				(int)(i / scale.y)}, t->width, t->height);
		color = color_shade(color, ray->lenght / 3);
		if (zz + i > 0)
			image_put_pixel(game->window, (t_vec){n, zz + i}, color);
		i++;
	}
}

void	walls_draw_texture(t_game *game, t_ray *ray, int n)
{
	t_texture	*texture;

	if (ray->texture == T_DOOR_OPEN || ray->texture == T_DOOR_CLOSE)
	{
		if (ray->texture == T_DOOR_OPEN)
			texture = game->config->doors_txt[DOOR_OPEN];
		else
			texture = game->config->doors_txt[DOOR_CLOSE];
	}
	else
	{
		if (ray->type == HORIZONTAL && ray->pos.y < game->player->position.y)
			texture = game->config->walls_txt[NORTH];
		else if (ray->type == HORIZONTAL)
			texture = game->config->walls_txt[SOUTH];
		else if (ray->type == VERTICAL && ray->pos.x < game->player->position.x)
			texture = game->config->walls_txt[EAST];
		else
			texture = game->config->walls_txt[WEST];
	}
	walls_draw_slice(game, n, ray, texture);
}
