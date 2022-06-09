/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:55:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 15:42:48 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

#include "config/config.h"
# include <game/game.h>
# include <utils/vec.h>

typedef struct s_ray	t_ray;
enum	e_ray_type {
	VERTICAL,
	HORIZONTAL
};

enum	e_texture_type {
	T_DOOR_OPEN,
	T_DOOR_CLOSE,
	T_WALL,
	T_NONE
};

struct s_ray
{
	double				lenght;
	t_vec				position;
	enum e_ray_type		type;
	enum e_texture_type	texture;
	
};

t_ray	raycaster(t_game *game, double direction);

#endif
