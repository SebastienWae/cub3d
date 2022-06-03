/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:54:25 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 14:16:46 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <graphics/window.h>
# include <utils/vec.h>

void	image_destructor(t_window *window);
t_image	*image_constructor(t_window *window);
void	image_put_pixel(t_image *img, t_vec coord, int color);

#endif
