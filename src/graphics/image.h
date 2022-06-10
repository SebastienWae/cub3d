/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:54:25 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/10 16:13:39 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <graphics/window.h>
# include <game/game.h>
# include <utils/vec.h>

void			image_destructor(t_window *window, t_image *image);
t_image			*image_constructor(t_window *window, void *img);
void			image_draw_rectangle(t_window *w, t_vec c, t_vec s, int color);
void			image_put_pixel(t_window *w, t_vec coord, unsigned int color);
unsigned int	image_get_pixel(t_image *img, t_vec coord, int w, int h);

#endif
