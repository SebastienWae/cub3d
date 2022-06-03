/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:24:26 by seb               #+#    #+#             */
/*   Updated: 2022/06/03 14:38:44 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <utils/vec.h>

typedef struct s_player
{
	double	direction;
	t_vec	position;
}	t_player;

t_player	*player_constructor(void);
void		player_destructor(t_player *player);

#endif
