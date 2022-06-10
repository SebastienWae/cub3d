/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:22:47 by seb               #+#    #+#             */
/*   Updated: 2022/06/10 11:47:59 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALLS_H
# define WALLS_H

# include <game/game.h>
# include <graphics/raycaster.h>

void	walls_draw_texture(t_game *game, t_ray *ray, int n);

#endif
