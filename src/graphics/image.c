/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:55:33 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 15:24:56 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <graphics/image.h>
#include <graphics/window.h>

void	image_put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	image_destructor(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img->img);
	free(window->img);
}

t_image	*image_constructor(t_window *window)
{
	t_image	*image;

	image = ft_calloc(1, sizeof(t_image));
	if (!image)
		return (NULL);
	image->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &(image->bits_per_pixel),
			&(image->line_length), &(image->endian));
	return (image);
}
