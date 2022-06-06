/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:24:26 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 09:29:28 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <utils/vec.h>

typedef struct s_player
{
	double	direction;
	t_vec	position;
	t_vec	delta;
}	t_player;

t_player	*player_constructor(void);
void		player_destructor(t_player *player);

#endif
