/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:58:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 15:37:07 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/raycaster.h"
#include "graphics/draw.h"
#include <math.h>
#include <game/game.h>
#include <utils/vec.h>

static t_bool	is_in_map(t_game *game, double x, double y)
{		
	if ((int)(y / game->config->scale) >= game->config->map_height || x < 0 || y < 0)
		return (FALSE);
	if (x / game->config->scale
		>= ft_strlen(game->config->map[(int)(y / game->config->scale)]))
		return (FALSE);
	return (TRUE);
}

static double	raycaster_get_distance_h(t_game *game, double direction, t_vec r)
{
	int	y;
	int	x;

	if (!is_in_map(game, r.x, r.y))
		return (-1);
	y = r.y / game->config->scale;
	x = r.x / game->config->scale;
	if (game->config->map[y][x] == '1' 
		|| game->config->map[y][x] == ' ')
	{
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
	}	
	else if (direction > 0 && direction < M_PI && is_in_map(game, x * game->config->scale, (y + 1) * game->config->scale)
		&& (game->config->map[y + 1][x] == '1' 
		|| game->config->map[y + 1][x] == ' '))
	{
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
	}
	return (0);
}

static double	raycaster_get_distance_v(t_game *game, double direction, t_vec r)
{
	int	y;
	int	x;

	if (!is_in_map(game, r.x, r.y))
		return (-1);
	y = r.y / game->config->scale;
	x = r.x / game->config->scale;
	if (game->config->map[y][x] == '1' 
		|| game->config->map[y][x] == ' ')
	{
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
	}
	else if (direction < M_PI / 2 && direction > 3 * M_PI_2 && is_in_map(game, x * game->config->scale, (y - 1) * game->config->scale)
		&& (game->config->map[y - 1][x] == '1' 
		|| game->config->map[y - 1][x] == ' '))
	{
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
	}
	return (0);
}

static double	raycaster_horizontal(t_game *game, double direction)
{
	t_vec	r;
	double	prev_y;
	double	dis;


	r = game->player->position;
	while (direction != 0 && direction != M_PI)
	{
		prev_y = r.y;
		if (direction < M_PI)
		{
			r.y = (floor((r.y / game->config->scale))
					* game->config->scale) - 0.0001;
			r.x = r.x + ((prev_y - r.y) / tan(direction));
		}
		else
		{			
			r.y = (floor((r.y / game->config->scale))
					* game->config->scale) + game->config->scale;
			r.x = r.x + ((prev_y - r.y) / tan(direction));
		}
		dis = raycaster_get_distance_h(game, direction, r);
		if (dis)
			return (dis);
		if (dis < 0)
			return (-1);
	}
	return (0);
}

static double	raycaster_vertical(t_game *game, double direction)
{
	t_vec	r;
	double	prev_x;
	double	dis;

	r = game->player->position;
	while (direction != M_PI_2 && direction != (M_PI * 3 / 2))
	{	
		prev_x = r.x;
		if (direction > M_PI_2 && direction < (M_PI * 3 / 2))
		{
//TODO : add +0.0001 if prevx = rx
			r.x = (floor(r.x / (double)game->config->scale)
					* game->config->scale) - 0.0001;
			r.y = r.y + ((prev_x - r.x) * tan(direction));
		}
		else
		{
//TODO : try to add + 0.0001 to x if x = prevx : x may stay the same with floor? 
			r.x = (floor(r.x / game->config->scale)
					* game->config->scale) + game->config->scale;
			r.y = r.y - ((r.x - prev_x) * tan(direction));
		}		
		dis = raycaster_get_distance_v(game, direction, r);
		if (dis)
			return (dis);
		if (dis < 0)
			return (-1);

	}	
	return (0);
}

t_ray	raycaster(t_game *game, double direction)
{
	double	horizontal_ray;
	double	vertical_ray;
	t_ray	ray;

	if (direction >= M_PI * 2)
			direction = direction - M_PI * 2;
	else if (direction < 0)
			direction = direction + M_PI * 2;	
	horizontal_ray = raycaster_horizontal(game, direction);
	vertical_ray = raycaster_vertical(game, direction);
	ray = (t_ray){0, 'N'};
	if (vertical_ray <= 0 || (horizontal_ray <= vertical_ray
		&& horizontal_ray > 0))
	{
		ray.type = 'H';
		ray.distance = horizontal_ray;
		return (ray);
	}
	else if (horizontal_ray <= 0 || (vertical_ray < horizontal_ray
		&& vertical_ray > 0))
	{
		ray.type = 'V';
		ray.distance = vertical_ray;
		return (ray);
	}
	return (ray);
}
