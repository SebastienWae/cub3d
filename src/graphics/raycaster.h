/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:55:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 10:58:16 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <game/game.h>
# include <utils/vec.h>

typedef enum e_ray_type {
	VERTICAL,
	HORIZONTAL
}	t_ray_type;

typedef enum t_texture_type {
	T_DOOR_OPEN,
	T_DOOR_CLOSE,
	T_WALL,
	T_NONE
}	t_txt_type;

typedef struct s_ray
{
	double		lenght;
	t_vec		pos;
	t_ray_type	type;
	t_txt_type	texture;
}	t_ray;

t_ray		raycaster(t_game *game, double direction);

t_bool		raycaster_is_in_map(t_game *game, t_vec p);
t_txt_type	raycaster_get_elem(t_game *g, t_vec p, t_ray_type t);
int			raycaster_door_opening(t_game *g, t_vec p, t_ray_type t, t_vec m);

#endif
