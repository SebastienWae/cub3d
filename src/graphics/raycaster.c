/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:31:34 by seb               #+#    #+#             */
/*   Updated: 2022/06/08 16:14:31 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <utils/bool.h>
#include <utils/vec.h>

static t_bool	is_in_map(t_game *game, t_vec p)
{
	int	x;
	int	y;

	x = (int)p.x >> 6;
	y = (int)p.y >> 6;
	if (x < 0 || y < 0)
		return (FALSE);
	if (y > game->config->map_height - 1)
		return (FALSE);
	if ((size_t)x > ft_strlen(game->config->map[y]) - 1)
		return (FALSE);
	return (TRUE);
}

static enum e_texture_type	is_blocking(t_game *game, t_vec p, enum e_ray_type type)
{
	int	x;
	int	y;

	x = (int)p.x >> 6;
	y = (int)p.y >> 6;
	if (x < 0 || y < 0 || !is_in_map(game, p))
		return (T_WALL);
	if (game->config->map[y][x] == '1' || game->config->map[y][x] == ' ')
		return (T_WALL);
	if ((game->config->map[y][x] == 'D'
		|| game->config->map[y][x] == 'O')
		&& game->config->map[y][x - 1] == '1' 
		&& game->config->map[y][x + 1] == '1' 
		&& type == HORIZONTAL)
	{
		if (game->config->map[y][x] == 'O')
		{
			int mod = ((int)p.x) % 64;
			if (((mod >= 0 && mod <= 8) || (mod  >= 56 && mod <= 64)))
				return (T_DOOR_OPEN);
		}
		else
			return (T_DOOR_CLOSE);	
	}
	if ((game->config->map[y][x] == 'D'
		|| game->config->map[y][x] == 'O')
		&& game->config->map[y + 1][x] == '1' 
		&& game->config->map[y - 1][x] == '1' 
		&& type == VERTICAL)
	{
		if (game->config->map[y][x] == 'O')
		{
			int mod = ((int)p.y) % 64;
			if (((mod >= 0 && mod <= 8) || (mod  >= 56 && mod <= 64)))
				return (T_DOOR_OPEN);
		}
		else
			return (T_DOOR_CLOSE);
	}			
	return (T_NONE);
}

static t_ray	ray_vertical(t_game *g, t_vec p, double ra, double tr)
{
	t_ray	r;
	double	o;
	double	oo;

	if (cos(ra) > 0.001)
	{
		r.position.x = (((int)p.x >> 6) << 6) + 64;
		r.position.y = (p.x - r.position.x) * tr + p.y;
		o = 64;
	}
	else if (cos(ra) < -0.001)
	{
		r.position.x = (((int)p.x >> 6) << 6) - 0.0001;
		r.position.y = (p.x - r.position.x) * tr + p.y;
		o = -64;
	}
	else
		return ((t_ray){-1, (t_vec){-1, -1}, VERTICAL, T_NONE});
	while (is_in_map(g, r.position))
	{
		if (cos(ra) > 0.001)
			oo = 32;
		else if (cos(ra) < -0.001)
			oo = -32;
		if (is_blocking(g, r.position, VERTICAL) == T_WALL)
			return ((t_ray){0, r.position, VERTICAL, T_WALL});
		else
		{
			r.texture =  is_blocking(g, (t_vec){r.position.x + oo, r.position.y + (-oo * tr)}, VERTICAL);
			if (r.texture == T_DOOR_OPEN || r.texture == T_DOOR_CLOSE)
				return ((t_ray){0, (t_vec){r.position.x + oo, r.position.y + (-oo * tr)}, VERTICAL, r.texture});
			else
				r.position = (t_vec){.x = r.position.x + o, .y = r.position.y + (-o * tr)};
		}
	}
	return ((t_ray){-1, (t_vec){-1, -1}, VERTICAL, T_NONE});
}

static t_ray	ray_horizontal(t_game *g, t_vec p, double ra, double tr)
{
	t_ray	r;
	int		o;
	double	oo;

	if (sin(ra) > 0.001)
	{
		r.position.y = (((int)p.y >> 6) << 6) - 0.0001;
		r.position.x = (p.y - r.position.y) * tr + p.x;
		o = -64;
	}
	else if (sin(ra) < -0.001)
	{
		r.position.y = (((int)p.y >> 6) << 6) + 64;
		r.position.x = (p.y - r.position.y) * tr + p.x;
		o = 64;
	}
	else
		return ((t_ray){-1, (t_vec){-1, -1}, HORIZONTAL, T_NONE});
	while (is_in_map(g, r.position))
	{
		if (sin(ra) > 0.001)
				oo = -32;
		else if (sin(ra) < -0.001)
				oo = 32;
		if (is_blocking(g, r.position, HORIZONTAL) == T_WALL)
			return ((t_ray){0, r.position, HORIZONTAL, T_WALL});
		else 
		{
			r.texture = is_blocking(g, (t_vec){r.position.x + (-oo * tr), r.position.y + oo}, HORIZONTAL);
			if (r.texture == T_DOOR_OPEN || r.texture == T_DOOR_CLOSE)
				return ((t_ray){0, (t_vec){r.position.x + (-oo * tr), r.position.y + oo}, HORIZONTAL, r.texture});
			else
				r.position = (t_vec){.x = r.position.x + (-o * tr), .y = r.position.y + o};
		}	
	}
	return ((t_ray){-1, (t_vec){-1, -1}, HORIZONTAL, T_NONE});
}

t_ray	raycaster(t_game *game, double r)
{
	double	tr;
	t_ray	rv;
	t_ray	rh;

	tr = tan(r);
	rv = ray_vertical(game, game->player->position, r, tr);
	if (rv.position.x != -1 && rv.position.y != -1)
		rv.lenght = (cos(r) * (rv.position.x - game->player->position.x)
				- sin(r) * (rv.position.y - game->player->position.y));
	else
		rv.lenght = 1e30;
	rh = ray_horizontal(game, game->player->position, r, 1. / tr);
	if (rh.position.x != -1 && rh.position.y != -1)
		rh.lenght = (cos(r) * (rh.position.x - game->player->position.x)
				- sin(r) * (rh.position.y - game->player->position.y));
	else
		rh.lenght = 1e30;
	if (rv.lenght < rh.lenght)
		return (rv);
	else
		return (rh);
}
