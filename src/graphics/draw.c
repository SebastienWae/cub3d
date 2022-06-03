/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/03 16:06:31 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <libft.h>
#include <game/game.h>
#include <graphics/image.h>
#include <graphics/draw.h>
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
				(t_vec){coord.x + i.x, coord.y + i.y}, color);
			i.x++;
		}
		i.y++;
	}
}

void	draw_player(t_game *game)
{	
	double	i;

	i = game->player->direction - M_PI / 6;
	while (i <= game->player->direction + M_PI / 6)
	{			
		draw_rectangle(game, game->player->position, (t_vec){2, 2}, 0x0000EEC2);
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
				draw_rectangle(game,
					(t_vec){game->config->scale * x, game->config->scale * y},
					(t_vec){game->config->scale, game->config->scale},
					0x00404040);
			else if (game->config->map[y][x] == '0'
					|| game->config->map[y][x] == 'N'
					|| game->config->map[y][x] == 'E'
					|| game->config->map[y][x] == 'S'
					|| game->config->map[y][x] == 'W')
				draw_rectangle(game,
					(t_vec){game->config->scale * x, game->config->scale * y},
					(t_vec){game->config->scale, game->config->scale},
					0x00808080);
			x++;
		}
		y++;
	}
	draw_player(game);
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
		if (direction >= M_PI * 2)
				direction = direction - M_PI * 2;
		else if (direction < 0)
				direction = direction + M_PI * 2;
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
