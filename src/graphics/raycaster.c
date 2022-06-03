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

#include <math.h>
#include <game/game.h>
#include <utils/vec.h>

static t_bool	is_in_map(t_game *game, double x, double y)
{	
	if (y / game->config->scale >= game->config->map_height || x < 0 || y < 0)
		return (FALSE);
	if (x / game->config->scale
		>= ft_strlen(game->config->map[(int)(y / game->config->scale)]))
		return (FALSE);
	return (TRUE);
}

static double	raycaster_get_distance(t_game *game, double direction, t_vec r)
{
	int	y;
	int	x;

	y = r.y / game->config->scale;
	x = r.x / game->config->scale;
	if (!is_in_map(game, r.x, r.y))
		return (0);
	if (game->config->map[y][x] == '1')
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
	else if (direction > 0 && direction < M_PI && is_in_map(game, r.x, r.y + 1)
		&& game->config->map[y + 1][x] == '1')
		return (sqrt(((game->player->position.x - r.x)
					* (game->player->position.x - r.x))
				+ ((game->player->position.y - r.y)
					* (game->player->position.y - r.y))));
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
			r.y = (floor((r.y / (double)game->config->scale))
					* game->config->scale) - 0.01;
			r.x = r.x + ((prev_y - r.y) / tan(direction));
		}
		else
		{			
			r.y = (floor((r.y / (double)game->config->scale))
					* game->config->scale) + game->config->scale;
			r.x = r.x - ((r.y - prev_y) * tan(3 * M_PI_2 - direction));
		}
		dis = raycaster_get_distance(game, direction, r);
		if (dis)
			return (dis);
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
			r.x = (floor(r.x / (double)game->config->scale)
					* game->config->scale) - 0.01;
			r.y = r.y + ((prev_x - r.x) * tan(direction));
		}
		else
		{
			r.x = (floor(r.x / (double)game->config->scale)
					* game->config->scale) + game->config->scale;
			r.y = r.y - ((r.x - prev_x) * tan(direction));
		}		
		dis = raycaster_get_distance(game, direction, r);
		if (dis)
			return (dis);
	}	
	return (0);
}

double	raycaster(t_game *game, double direction)
{
	double	horizontal_ray;
	double	vertical_ray;

	horizontal_ray = raycaster_horizontal(game, direction);
	vertical_ray = raycaster_vertical(game, direction);
	if ((vertical_ray == 0 || horizontal_ray < vertical_ray)
		&& horizontal_ray > 0)
		return (horizontal_ray);
	else if ((horizontal_ray == 0 || vertical_ray <= horizontal_ray)
		&& vertical_ray > 0)
		return (vertical_ray);
	return (0);
}
