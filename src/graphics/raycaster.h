/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:55:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/05 17:37:15 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <game/game.h>
# include <utils/vec.h>

enum	e_ray_type {
	VERTICAL,
	HORIZONTAL
};

typedef struct s_ray
{
	double			lenght;
	t_vec			position;
	enum e_ray_type	type;
}	t_ray;

t_ray	raycaster(t_game *game, double direction);

#endif
