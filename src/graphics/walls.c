/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 11:33:30 by jeulliot         ###   ########.fr       */
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

static void	ceiling_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, 0},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[CEILING]);
}

static void	floor_draw(t_game *game)
{
	draw_rectangle(game,
		(t_vec){0, (int)(WINDOW_HEIGHT / 2)},
		(t_vec){WINDOW_WIDTH, (int)(WINDOW_HEIGHT / 2)},
		game->config->colors[FLOOR]);
}

static void	walls_draw_bigger_texture(t_game *game, int x, double w, int wall_height, t_texture *texture)
{
	int			i;
	double		scale;

	scale = (double)texture->height / wall_height;
	i = 0;
	while (i < wall_height)
	{
		draw_rectangle(game,
			(t_vec){x, (WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i},
			(t_vec){1, 1},
			image_get_pixel(texture->img,
				(t_vec)
			{
				(int)(w * 5) % texture->width,
				(int)(i * scale + i * scale / wall_height)
			},
				texture->width, texture->height));
		i ++;
	}
}

static void	walls_draw_smaller_texture(t_game *game, int x, double w, int wall_height, t_texture *texture)
{
	int			i;
	double		scale;

	scale = (double) wall_height / texture->height;
	i = 0;
	while (i <= wall_height - scale)
	{
		draw_rectangle(game,
			(t_vec){x, (WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i},
			(t_vec){1, scale},
			image_get_pixel(texture->img,
				(t_vec)
			{
				(int)(w * 5) % texture->width,
				(int)(i / scale)
			},
				texture->width, texture->height));
		i += scale;
	}
	while (i < wall_height)
	{
		draw_rectangle(game,
			(t_vec){x, (WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i},
			(t_vec){1, 1},
			image_get_pixel(texture->img,
				(t_vec)
			{
				(int)(w * 5) % texture->width,
				(int)(i / scale)
			},
				texture->width, texture->height));
		i ++;
	}
}

static void	walls_draw_slice(t_game *game, int x, double w, int wall_height, t_texture *texture)
{
	if (wall_height >= texture->height)
		walls_draw_smaller_texture(game, x, w, wall_height, texture);
	else
		walls_draw_bigger_texture(game, x, w, wall_height, texture);
}

static void	walls_draw_texture(t_game *game, t_ray *ray, int n, int wall_height)
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

void	walls_draw(t_game *game)
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
