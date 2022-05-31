/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:24:26 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 09:49:04 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <stddef.h>

typedef struct s_player
{
	double			direction;
	size_t			x;
	size_t			y;
}	t_player;

t_player	*player_constructor(void);
void		player_destructor(t_player *player);

#endif
