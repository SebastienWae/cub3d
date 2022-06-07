/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:22:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 11:43:32 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

# include <game/game.h>
# include <graphics/raycaster.h>

void	walls_draw_texture(t_game *game, t_ray *ray, int n, int wall_height);

#endif
