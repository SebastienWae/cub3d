/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:31:34 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 12:41:55 by seb              ###   ########.fr       */
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

static t_bool	is_blocking(t_game *game, t_vec p)
{
	int	x;
	int	y;

	x = (int)p.x >> 6;
	y = (int)p.y >> 6;
	if (game->config->map[y][x] == '1' || game->config->map[y][x] == ' ')
		return (TRUE);
	return (FALSE);
}

static double	raycaster_vertical(t_game *g, t_vec p, double ra, double tr)
{
	t_vec	r;
	double	o;

	if (cos(ra) > 0.001)
	{
		r.x = (((int)p.x >> 6) << 6) + 64;
		r.y = (p.x - r.x) * tr + p.y;
		o = 64;
	}
	else if (cos(ra) < -0.001)
	{
		r.x = (((int)p.x >> 6) << 6) - 0.0001;
		r.y = (p.x - r.x) * tr + p.y;
		o = -64;
	}
	else
		return (1e30);
	while (is_in_map(g, r))
	{
		if (is_blocking(g, r))
			return (cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y));
		else
			r = (t_vec){.x = r.x + o, .y = r.y + (-o * tr)};
	}
	return (1e30);
}

static double	raycaster_horizontal(t_game *g, t_vec p, double ra, double tr)
{
	t_vec	r;
	int		o;

	if (sin(ra) > 0.001)
	{
		r.y = (((int)p.y >> 6) << 6) - 0.0001;
		r.x = (p.y - r.y) * tr + p.x;
		o = -64;
	}
	else if (sin(ra) < -0.001)
	{
		r.y = (((int)p.y >> 6) << 6) + 64;
		r.x = (p.y - r.y) * tr + p.x;
		o = 64;
	}
	else
		return (1e30);
	while (is_in_map(g, r))
	{
		if (is_blocking(g, r))
			return (cos(ra) * (r.x - p.x) - sin(ra) * (r.y - p.y));
		else
			r = (t_vec){.x = r.x + (-o * tr), .y = r.y + o};
	}
	return (1e30);
}

t_ray	raycaster(t_game *game, double r)
{
	double	tr;
	double	rv;
	double	rh;

	tr = tan(r);
	rv = raycaster_vertical(game, game->player->position, r, tr);
	rh = raycaster_horizontal(game, game->player->position, r, 1. / tr);
	if (rv < rh)
		return ((t_ray){.type = VERTICAL, .lenght = rv});
	else
		return ((t_ray){.type = HORIZONTAL, .lenght = rh});
}
