/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:59:51 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 15:05:24 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <game/game.h>

typedef struct s_ray {
    double  distance;
    char    type;
} t_ray;

t_ray	raycaster(t_game *game, double direction);

#endif
