/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:58:20 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 15:05:12 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <game/game.h>

double	raycaster(t_game *game, double direction)
{
	double	xa;
	double	ya;
	double	prev_ya;
	double	xb;
	double	yb;
	double	prev_xb;
	double	da;
	double	db;
	double	px;
	double	py;

	xa = x;
	ya = y;
	xb = x;
	yb = y;
	da = 0;
	db = 0;
	px = x;
	py = y;
	if (direction >= M_PI * 2)
			direction = direction - M_PI * 2;
	else if (direction < 0)
			direction = direction + M_PI * 2;
	while (direction != 0 && direction != M_PI) // horizontal
	{		
		prev_ya = ya;
		if (direction < M_PI)
		{
			ya = (floor((ya / (double)game->config->scale)) * game->config->scale) - 0.01;
			xa = xa + ((prev_ya - ya) / tan(direction));
		}
		else
		{			
			ya = (floor((ya / (double)game->config->scale)) * game->config->scale) + game->config->scale;
			xa = xa - ((ya - prev_ya) * tan(3 * M_PI_2 - direction));
		}
		if (!is_in_map(game, xa, ya))
			break ;
		if (game->config->map[(int)(ya/game->config->scale)][(int)(xa/game->config->scale)] == '1')
		{	
			da = sqrt(((px - xa) * (px - xa)) + ((py - ya) * (py - ya)));
			break ;
		}
		else if (direction > 0 && direction < M_PI && is_in_map(game, xa, ya + 1) && game->config->map[(int)ya/game->config->scale + 1][(int)xa/game->config->scale] == '1')
		{
			da = sqrt(((px - xa) * (px - xa)) + ((py - ya) * (py - ya)));
			break ;
		}
	}
	while (direction != M_PI_2 && direction != (M_PI * 3 / 2)) // vertical
	{
		prev_xb = xb;
		if (direction > M_PI_2 && direction < (M_PI * 3 / 2))
		{
			xb = (floor(xb / (double)game->config->scale) * game->config->scale) - 0.01;
			yb = yb + ((prev_xb - xb) * tan(direction));
		}
		else
		{
			xb = (floor(xb / (double)game->config->scale) * game->config->scale) + game->config->scale;
			yb = yb - ((xb - prev_xb) * tan(direction));
		}		
		if (!is_in_map(game, xb, yb))
			break ;
		if (game->config->map[(int)(yb/game->config->scale)][(int)(xb/game->config->scale)] == '1')
		{	
			db = sqrt(((px - xb) * (px - xb)) + ((py - yb) * (py - yb)));
			break ;
		}	
		else if (direction > M_PI && direction < 2 * M_PI && is_in_map(game, xb, yb - 1) && game->config->map[(int)((yb - 1)/game->config->scale)][(int)xb/game->config->scale] == '1')
		{			
			db = sqrt(((px - xb) * (px - xb)) + ((py - yb) * (py - yb)));
			break ;
		}	
	}	
	if ((db == 0 || da < db) && da > 0 && is_in_map(game, xa, ya))
		return (da);
	else if ((da == 0 || db <= da) && db > 0 && is_in_map(game, xb, yb))
		return (db);
	return (0);
}
