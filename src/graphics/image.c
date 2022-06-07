/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:55:33 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/07 15:59:51 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <graphics/image.h>
#include <graphics/window.h>
#include <utils/vec.h>

void	image_put_pixel(t_image *img, t_vec coord, int color)
{
	char	*pixel;

	if (coord.x >= 0 && coord.y >= 0
		&& coord.x < WINDOW_WIDTH && coord.y < WINDOW_HEIGHT)
	{
		pixel = img->addr
			+ (int)(coord.y * img->line_length + coord.x
				* (int)(img->bits_per_pixel / 8));
		if (pixel)
			*(unsigned int *)pixel = color;
	}
	else
		return ;
}

void	image_destructor(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img->img);
	free(window->img);
}

t_image	*image_constructor(t_window *window, void *img)
{
	t_image	*image;

	image = ft_calloc(1, sizeof(t_image));
	if (!image)
		return (NULL);
	if (img)
		image->img = img;
	else
		image->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &(image->bits_per_pixel),
			&(image->line_length), &(image->endian));
	return (image);
}

unsigned int	image_get_pixel(t_image *img, t_vec coord, int width, int height)
{
	char	*pixel;

	if (coord.x >= 0 && coord.y >= 0
		&& coord.x < width && coord.y < height)
	{
		pixel = img->addr
			+ (int)(coord.y * img->line_length + coord.x
				* (int)(img->bits_per_pixel / 8));
		if (pixel)
			return (*(unsigned int *)pixel);
		else
			return (0);
	}
	return (0);
}
