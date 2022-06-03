/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:12 by seb               #+#    #+#             */
/*   Updated: 2022/06/03 14:15:31 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <game/game.h>
# include <utils/vec.h>

double	ray_caster(t_game *game, double direction);
void	draw_rectangle(t_game *game, t_vec pos, t_vec size, int color);
void	draw_player(t_game *game);
void	draw_mini_map(t_game *game);
void	draw_screen(t_game *game);

#endif
