/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 21:29:51 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stddef.h>
#include <game/game.h>
#include <graphics/image.h>

void	draw_ray(t_game *game, size_t x, size_t y, double direction, int color)
{
	double	i;
	double	j;

	i = 0;
	j = 0;
	while (y + j > 0
		&& y + j < WINDOW_HEIGHT
		&& x + i > 0
		&& x + i < WINDOW_WIDTH
		&& game->config->map[(int)((y + j)/game->config->scale)][(int)((x + i)/game->config->scale)] != '1')
	{
		image_put_pixel(game->window->img, x + i, y + j, color);
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

void	draw_player(t_game *game)
{	
	double	i;

	i = game->player->direction - M_PI / 6;
	draw_rectangle(game, game->player->x - game->config->scale / 6,
		game->player->y - game->config->scale / 6,
		game->config->scale / 3, game->config->scale / 3, 0x0000EEC2);
	while (i <= game->player->direction + M_PI / 6)
	{
		draw_ray(game, game->player->x, game->player->y, i, 0x0000EEC2);
		i += M_PI / 60;
	}
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
