/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:31:34 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 11:09:11 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>
#include <config/map.h>
#include <graphics/raycaster.h>
#include <graphics/window.h>
#include <utils/bool.h>
#include <utils/vec.h>

static t_ray	ray_vcheck(t_game *g, t_ray r, double o, double tr)
{
	while (raycaster_is_in_map(g, r.pos))
	{
		if (raycaster_get_elem(g, r.pos, VERTICAL) == T_WALL)
			return ((t_ray){0, r.pos, VERTICAL, T_WALL});
		else
		{
			r.texture = raycaster_get_elem(g, (t_vec){r.pos.x + ((int)o >> 1),
					r.pos.y + (((int)-o >> 1) * tr)}, VERTICAL);
			if (r.texture == T_DOOR_OPEN || r.texture == T_DOOR_CLOSE)
				return ((t_ray){0, (t_vec){r.pos.x + ((int)o >> 1),
					r.pos.y + (((int)-o >> 1) * tr)}, VERTICAL, r.texture});
			else
				r.pos = (t_vec){r.pos.x + o, r.pos.y + (-o * tr)};
		}
	}
	return ((t_ray){-1, (t_vec){-1, -1}, VERTICAL, T_NONE});
}

static t_ray	ray_vertical(t_game *g, t_vec rp, double rr, double tr)
{
	t_ray	r;
	double	o;

	if (cos(rr) > 0.001)
	{
		r.pos.x = (((int)rp.x >> 6) << 6) + 64;
		o = 64;
	}
	else if (cos(rr) < -0.001)
	{
		r.pos.x = (((int)rp.x >> 6) << 6) - 0.0001;
		o = -64;
	}
	else
		return ((t_ray){-1, (t_vec){-1, -1}, VERTICAL, T_NONE});
	r.pos.y = (rp.x - r.pos.x) * tr + rp.y;
	return (ray_vcheck(g, r, o, tr));
}

static t_ray	ray_hcheck(t_game *g, t_ray r, double o, double tr)
{
	while (raycaster_is_in_map(g, r.pos))
	{
		if (raycaster_get_elem(g, r.pos, HORIZONTAL) == T_WALL)
			return ((t_ray){0, r.pos, HORIZONTAL, T_WALL});
		else
		{
			r.texture = raycaster_get_elem(g, (t_vec){r.pos.x + (((int)(-o)
							>> 1) * tr), r.pos.y + ((int)o >> 1)}, HORIZONTAL);
			if (r.texture == T_DOOR_OPEN || r.texture == T_DOOR_CLOSE)
				return ((t_ray){0, (t_vec){r.pos.x + (((int)(-o) >> 1) * tr),
					r.pos.y + ((int)o >> 1)}, HORIZONTAL, r.texture});
			else
				r.pos = (t_vec){r.pos.x + (-o * tr), r.pos.y + o};
		}
	}
	return ((t_ray){-1, (t_vec){-1, -1}, HORIZONTAL, T_NONE});
}

static t_ray	ray_horizontal(t_game *g, t_vec rp, double rr, double tr)
{
	t_ray	r;
	int		o;

	if (sin(rr) > 0.001)
	{
		r.pos.y = (((int)rp.y >> 6) << 6) - 0.0001;
		o = -64;
	}
	else if (sin(rr) < -0.001)
	{
		r.pos.y = (((int)rp.y >> 6) << 6) + 64;
		o = 64;
	}
	else
		return ((t_ray){-1, (t_vec){-1, -1}, HORIZONTAL, T_NONE});
	r.pos.x = (rp.y - r.pos.y) * tr + rp.x;
	return (ray_hcheck(g, r, o, tr));
}

t_ray	raycaster(t_game *game, double rr)
{
	double	tr;
	t_ray	rv;
	t_ray	rh;

	tr = tan(rr);
	rv = ray_vertical(game, game->player->position, rr, tr);
	if (rv.pos.x != -1 && rv.pos.y != -1)
		rv.lenght = (cos(rr) * (rv.pos.x - game->player->position.x)
				- sin(rr) * (rv.pos.y - game->player->position.y));
	else
		rv.lenght = 1e30;
	rh = ray_horizontal(game, game->player->position, rr, 1. / tr);
	if (rh.pos.x != -1 && rh.pos.y != -1)
		rh.lenght = (cos(rr) * (rh.pos.x - game->player->position.x)
				- sin(rr) * (rh.pos.y - game->player->position.y));
	else
		rh.lenght = 1e30;
	if (rv.lenght < rh.lenght)
		return (rv);
	else
		return (rh);
}
