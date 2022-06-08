/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:40:04 by jeulliot          #+#    #+#             */
/*   Updated: 2022/06/08 16:34:26 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <game/game.h>
#include <graphics/raycaster.h>

void	door_toggle(t_game *game)
{
	// t_ray	ray;

	// ray = raycaster(game, game->player->direction);
	// if ((int)ray.lenght >> 6 < 64)
	// {
	// 	if (game->config->map[(int)ray.position.y >> 6][(int)ray.position.x >> 6] == 'D')
	// 	{
	// 		game->config->map[(int)ray.position.y >> 6][(int)ray.position.x >> 6] = 'O';
	// 		game->window->redraw = TRUE;
	// 	}
	// 	else if (game->config->map[(int)ray.position.y >> 6][(int)ray.position.x >> 6] == 'O')
	// 	{
	// 		game->config->map[(int)ray.position.y >> 6][(int)ray.position.x >> 6] = 'D';
	// 		game->window->redraw = TRUE;
	// 	}
	// }

	int	colx;
	int	coly;


	colx = (int)(game->player->position.x + game->player->delta.x * 64) >> 6;
	coly = (int)(game->player->position.y + game->player->delta.y * 64) >> 6;
	if (game->config->map[coly][colx] == 'D')
	{
		game->config->map[coly][colx] = 'O';
		game->window->redraw = TRUE;
	}
	else if (game->config->map[coly][colx] == 'O')
	{
		game->config->map[coly][colx] = 'D';
		game->window->redraw = TRUE;
	}
}