/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:23:32 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 12:44:17 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <game/player.h>
#include <utils/vec.h>

t_player	*player_constructor(void)
{
	t_player	*player;

	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	return (player);
}

void	player_destructor(t_player *player)
{
	*player = (t_player)
	{
		.direction = 0,
		.position = (t_vec){0, 0},
		.delta = (t_vec){0, 0},
	};
	free(player);
}
