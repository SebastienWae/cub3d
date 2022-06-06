/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/06 18:09:26 by jeulliot         ###   ########.fr       */
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

static void	walls_draw_slice(t_game *game, int x, t_ray *ray, int wall_height, t_texture *texture)
{
	int			i;
	double		scale;

	scale = (double) wall_height / texture->height;
	i = 0;
	while (i <= wall_height - scale)
	{
		draw_rectangle(game,
			(t_vec)
			{
				x,
				(WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i
			},
			(t_vec){1, scale}, image_get_pixel(texture->img, (t_vec)
			{
				(int)(ray->position.x * 5) % texture->width,
				(int)(i / scale)
			},
			texture->width,
			texture->height));
		i += scale;
	}
	while (i < wall_height)
	{
		draw_rectangle(game,
			(t_vec)
			{
				x,
				(WINDOW_HEIGHT / 2.) - (wall_height / 2.) + i
			},
			(t_vec){1, 1}, image_get_pixel(texture->img, (t_vec)
			{
				(int)(ray->position.x * 5) % texture->width,
				(int)(i / scale)
			},
			texture->width,
			texture->height));
		i ++;
	}
}

static void	walls_draw_texture(t_game *game, t_ray *ray, int ray_r, int n, int wall_height)
{
	if (ray->type == HORIZONTAL 
		&& ray_r < M_PI - M_PI / 6
		&& ray_r > M_PI / 6)
		walls_draw_slice(game, n, ray, wall_height, game->config->textures[NORTH]);		
	else if (ray->type == HORIZONTAL 
		&& ray_r >= M_PI + M_PI / 6
		&& ray_r <= 2 * M_PI - M_PI / 6)
		walls_draw_slice(game, n, ray, wall_height, game->config->textures[SOUTH]);
	else if (ray->type == VERTICAL 
		&& ray_r >= M_PI_2 + M_PI / 6
		&& ray_r <= 3 * M_PI_2 - M_PI / 6)
		walls_draw_slice(game, n, ray, wall_height, game->config->textures[WEST]);
	else 
		walls_draw_slice(game, n, ray, wall_height, game->config->textures[EAST]);	
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
	walls_draw_texture(game, &ray, ray_r, n, wall_height);
	/*if (ray.type == HORIZONTAL 
		&& ray_r < M_PI 
		&& ray_r > 0)
		draw_rectangle(game,
			(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
			(t_vec){1, wall_height}, 0x00505050);
	else if (ray.type == HORIZONTAL 
		&& ray_r >= M_PI 
		&& ray_r <= 2 * M_PI)
		draw_rectangle(game,
			(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
			(t_vec){1, wall_height}, 0x00FF0000);
	else if (ray.type == VERTICAL 
		&& ray_r >= M_PI_2 
		&& ray_r <= 3 * M_PI_2)
		draw_rectangle(game,
			(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
			(t_vec){1, wall_height}, 0x00454545);
	else 
		draw_rectangle(game,
		(t_vec){n, (WINDOW_HEIGHT / 2.) - (wall_height / 2.)},
		(t_vec){1, wall_height}, 0x0000FF00);		*/
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
	/*	if (ray_r < 0)
			ray_r += M_PI * 2;*/
		w++;
	}
}
