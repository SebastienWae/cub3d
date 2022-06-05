/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:31:34 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 17:49:28 by seb              ###   ########.fr       */
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

static t_vec	ray_vertical(t_game *g, t_vec p, double ra, double tr)
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
		return ((t_vec){-1, -1});
	while (is_in_map(g, r))
	{
		if (is_blocking(g, r))
			return (r);
		else
			r = (t_vec){.x = r.x + o, .y = r.y + (-o * tr)};
	}
	return ((t_vec){-1, -1});
}

static t_vec	ray_horizontal(t_game *g, t_vec p, double ra, double tr)
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
		return ((t_vec){-1, -1});
	while (is_in_map(g, r))
	{
		if (is_blocking(g, r))
			return (r);
		else
			r = (t_vec){.x = r.x + (-o * tr), .y = r.y + o};
	}
	return ((t_vec){-1, -1});
}

t_ray	raycaster(t_game *game, double r)
{
	double	tr;
	t_ray	rv;
	t_ray	rh;

	tr = tan(r);
	rv = (t_ray){.type = VERTICAL,
		.position = ray_vertical(game, game->player->position, r, tr)};
	if (rv.position.x != -1 && rv.position.y != -1)
		rv.lenght = (cos(r) * (rv.position.x - game->player->position.x)
				- sin(r) * (rv.position.y - game->player->position.y));
	else
		rv.lenght = 1e30;
	rh = (t_ray){.type = HORIZONTAL,
		.position = ray_horizontal(game, game->player->position, r, 1. / tr)};
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
