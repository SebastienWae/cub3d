/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/03 15:02:03 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils/bool.h"
#include <mlx.h>
#include <math.h>
#include <stddef.h>
#include <game/game.h>
#include <graphics/image.h>
#include <graphics/draw.h>

void	draw_cone(t_game *game, size_t x, size_t y, double direction, int color)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while ((int) sqrt(i * i + j * j) < (int)(game->config->scale) / 2)
	{
		draw_rectangle(game, x + i, y + j, 1, 1, color);
		i = i + cos(direction);
		j = j - sin(direction);
	}
}

void	draw_rectangle(t_game *game, size_t x, size_t y, size_t size_x, size_t size_y, int color)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			image_put_pixel(game->window->img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

t_bool is_in_map(t_game *game, double x, double y)
{	
	if (y / game->config->scale >= game->config->map_height || x < 0 || y < 0)
		return (FALSE);
	if (x / game->config->scale >= ft_strlen(game->config->map[(int)(y / game->config->scale)]))
		return (FALSE);
	return (TRUE);
}

void	draw_player(t_game *game)
{	
	double	i;

	i = game->player->direction - M_PI / 6;
	while (i <= game->player->direction + M_PI / 6)
	{			
		draw_cone(game, game->player->x, game->player->y, i, 0x0000EEC2);
		i += M_PI / 60;
	}
	i = game->player->direction - M_PI / 6;
}

void	draw_mini_map(t_game *game)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < game->config->map_height)
	{
		x = 0;
		while (x < ft_strlen(game->config->map[y]))
		{
			if (game->config->map[y][x] == '1')
				draw_rectangle(game, game->config->scale * x,
					game->config->scale * y, game->config->scale,
					game->config->scale, 0x00404040);
			else if (game->config->map[y][x] == '0'
					|| game->config->map[y][x] == 'N'
					|| game->config->map[y][x] == 'E'
					|| game->config->map[y][x] == 'S'
					|| game->config->map[y][x] == 'W')
				draw_rectangle(game, game->config->scale * x,
					game->config->scale * y, game->config->scale,
					game->config->scale, 0x00808080);
			x++;
		}
		y++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->window->mlx, game->window->win, game->window->img->img, 0, 0);
}

void	draw_screen(t_game *game)
{
	double	proj_distance;
	double	ray_angle;
	double	distance_to_wall;
	int		i;
	double	direction;
	double	dist;
	double	line_height;

	draw_rectangle(game, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2, game->config->colors[CEILING]);
	draw_rectangle(game, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, game->config->colors[FLOOR]);
	proj_distance = WINDOW_HEIGHT / tan (M_PI / 3);
	ray_angle = (M_PI / 3) / WINDOW_WIDTH;
	i = WINDOW_WIDTH - 1;
	direction = game->player->direction - M_PI / 6;
	while (i > 0 && direction - game->player->direction < M_PI / 3)
	{	
		dist = ray_caster(game, game->player->x, game->player->y, direction, 0x0000EEC2);
		distance_to_wall = cos(direction - game->player->direction) * dist;
		line_height = game->config->scale / distance_to_wall * proj_distance;
		if ((int)((double)(WINDOW_HEIGHT / 2) - (line_height / 2) + line_height) < WINDOW_HEIGHT
		&& (int)((double)(WINDOW_HEIGHT / 2) - (line_height / 2) + line_height) > 0)
			draw_rectangle(game, i, (int)((WINDOW_HEIGHT / 2) - (game->config->scale / distance_to_wall * proj_distance / 2)), 1, line_height, 0x0050585D);
		else if (line_height >= WINDOW_HEIGHT)
			draw_rectangle(game, i, 0, 1, WINDOW_HEIGHT - 1, 0x0050585D);
		direction += ray_angle;
		i--;
	}	
}
