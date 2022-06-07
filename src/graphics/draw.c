/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:19 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 09:17:23 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game/game.h>
#include <graphics/draw.h>
#include <graphics/image.h>
#include <utils/vec.h>

void	draw_rectangle(t_game *game, t_vec coord, t_vec size, int color)
{
	t_vec	i;

	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			image_put_pixel(game->window->img,
				(t_vec){(int)(coord.x + i.x), (int)(coord.y + i.y)}, color);
			i.x++;
		}
		i.y++;
	}
}
