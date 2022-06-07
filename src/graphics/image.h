/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:54:25 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/08 00:06:03 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <graphics/window.h>
# include <utils/vec.h>

void			image_destructor(t_window *window);
t_image			*image_constructor(t_window *window, void *img);
void			image_put_pixel(t_image *img, t_vec coord, int color);
unsigned int	image_get_pixel(t_image *img, t_vec coord, int w, int h);
#endif
