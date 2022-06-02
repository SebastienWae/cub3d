/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/02 14:06:40 by jeulliot         ###   ########.fr       */
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
	// while ((int) sqrt(i * i + j * j) < (int)(game->config->scale / 2))
	while ((int) sqrt(i * i + j * j) < (int)(game->config->scale))
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

t_bool is_in_map(t_game *game, size_t x, size_t y)
{
	if (y / game->config->scale >= game->config->map_height)
		return (FALSE);
	if (x / game->config->scale >= ft_strlen(game->config->map[y / game->config->scale]))
		return (FALSE);
	return (TRUE);
}


double	draw_ray(t_game *game, size_t x, size_t y, double direction, int color)
{
	size_t	xa;
	size_t	ya;
	size_t	prev_ya;
	size_t	xb;
	size_t	yb;
	size_t	prev_xb;
	double	da;
	double	db;
	xa = x;
	ya = y;
	xb = x;
	yb = y;
	da = 0;
	db = 0;
	if (direction >= M_PI * 2)
			direction = direction - M_PI * 2;
	else if (direction < 0)
			direction = direction + M_PI * 2;	
	while (direction != 0 && direction != M_PI)
	{		
		prev_ya = ya;
		if (direction < M_PI)
		{
			ya = (floor((int)(ya / game->config->scale)) * game->config->scale) - 1;
			xa = xa + ((prev_ya - ya) / tan(direction));
		}
		else
		{			
			ya = (floor((int)(ya / (double)game->config->scale)) * game->config->scale) + game->config->scale;
			xa = xa - ((ya - prev_ya) * tan(3 * M_PI_2 - direction));			
		}	
		if (!is_in_map(game, xa, ya))
			break;
		if (game->config->map[ya/game->config->scale][xa/game->config->scale] == '1')
		{
			da = sqrt(((x - xa) * (x - xa)) + ((y - ya) * (y - ya)));;
			break;
		}		
		

	}
	while (direction != M_PI_2 && direction != (M_PI * 3 / 2))
	{
		prev_xb = xb;
		if (direction > M_PI_2 && direction < (M_PI * 3 / 2))
		{
			xb = (floor((int)xb / (double)game->config->scale) * game->config->scale) - 1;
			yb = yb + ((prev_xb - xb) * tan(direction));
		}
		else
		{
			xb = (floor((int)xb / (double)game->config->scale) * game->config->scale) + game->config->scale;
			yb = yb - ((xb - prev_xb) * tan(direction));
			
		}		
		if (!is_in_map(game, xb, yb))
			break;
		if (game->config->map[yb/game->config->scale][xb/game->config->scale] == '1')
		{
			db = sqrt(((x - xb) * (x - xb)) + ((y - yb) * (y - yb)));
			break;
		}
		/*
		else if (direction > M_PI_2 && direction < 3 * M_PI_2 && game->config->map[yb/game->config->scale - 1][xb/game->config->scale + 1] == '1')
		{
			db = sqrt(((x - xb) * (x - xb)) + ((y - yb) * (y - yb)));			
			break;
		}*/
		
	}
	
	if ((db == 0 || da < db) && is_in_map(game, xa, ya))
	{
		draw_rectangle(game, xa, ya, 2, 2, color);
		return (da);
	}
	else if ((da == 0 || db <= da) && is_in_map(game, xb, yb) )
	{
		draw_rectangle(game, xb, yb, 2, 2, 0x00FF0000);
		return (db);
	}
	return (0);
}

void	draw_player(t_game *game)
{	
	double	i;

	i = game->player->direction - M_PI / 6;
	//draw_rectangle(game, game->player->x - game->config->scale / 6,
	//	game->player->y - game->config->scale / 6,
	//	game->config->scale / 3, game->config->scale / 3, 0x0000EEC2);
	while (i <= game->player->direction + M_PI / 6)
	{			
		draw_cone(game, game->player->x, game->player->y, i, 0x0000EEC2);		
	 	i += M_PI / 60;
	}
	i = game->player->direction - M_PI / 6;
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
