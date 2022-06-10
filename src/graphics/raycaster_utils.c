/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:54:46 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 10:58:24 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <graphics/raycaster.h>
#include <utils/vec.h>

int	raycaster_door_opening(t_game *g, t_vec p, t_ray_type t, t_vec map)
{
	int	x;
	int	y;

	x = map.x;
	y = map.y;
	if ((g->config->map[y][x] == 'D'
		|| g->config->map[y][x] == 'O')
		&& g->config->map[y][x - 1] == '1'
		&& g->config->map[y][x + 1] == '1'
		&& t == HORIZONTAL)
		return (((int)p.x) % 64);
	else if ((g->config->map[y][x] == 'D'
		|| g->config->map[y][x] == 'O')
		&& g->config->map[y + 1][x] == '1'
		&& g->config->map[y - 1][x] == '1'
		&& t == VERTICAL)
		return (((int)p.y) % 64);
	return (-1);
}

t_txt_type	raycaster_get_elem(t_game *g, t_vec p, t_ray_type t)
{
	t_vec	map;
	int		door_opening;

	map.x = (int)p.x >> 6;
	map.y = (int)p.y >> 6;
	if (map.x < 0 || map.y < 0 || !raycaster_is_in_map(g, p)
		|| g->config->map[(int)map.y][(int)map.x] == '1'
		|| g->config->map[(int)map.y][(int)map.x] == ' ')
		return (T_WALL);
	door_opening = raycaster_door_opening(g, p, t, map);
	if (door_opening != -1)
	{
		if (g->config->map[(int)map.y][(int)map.x] == 'O')
		{
			if (((door_opening >= 0 && door_opening <= 8)
					|| (door_opening >= 56 && door_opening <= 64)))
				return (T_DOOR_OPEN);
		}
		else
			return (T_DOOR_CLOSE);
	}
	return (T_NONE);
}

t_bool	raycaster_is_in_map(t_game *game, t_vec p)
{
	int	x;
	int	y;

	x = (int)p.x >> 6;
	y = (int)p.y >> 6;
	if (x < 0 || y < 0)
		return (FALSE);
	if (y > game->config->map_height - 1)
		return (FALSE);
	if ((size_t)x > game->config->map_width -1)
		return (FALSE);
	return (TRUE);
}
