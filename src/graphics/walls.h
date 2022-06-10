/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:22:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 15:53:37 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

# include <game/game.h>
# include <graphics/raycaster.h>

void	walls_draw_texture(t_game *game, t_ray *ray, int n);

#endif
