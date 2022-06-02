/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:12 by seb               #+#    #+#             */
/*   Updated: 2022/06/02 16:10:44 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include <game/game.h>
# include <stddef.h>

double	ray_caster(t_game *game, size_t x, size_t y, double direction, int color);
void	draw_rectangle(t_game *game, size_t x, size_t y, size_t size_x, size_t size_y, int color);
void	draw_player(t_game *game);
void	draw_mini_map(t_game *game);
void	draw_screen(t_game *game);

#endif
