/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:55:33 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/09 21:38:33 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <graphics/image.h>
#include <graphics/window.h>
#include <utils/vec.h>

void	image_draw_rectangle(t_game *game, t_vec coord, t_vec size, int color)
{
	t_vec	i;

	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			image_put_pixel(game->window->img,
				(t_vec){(int)(coord.x + i.x), (int)(coord.y + i.y)}, color);
			i.x++;
		}
		i.y++;
	}
}

void	image_put_pixel(t_image *img, t_vec coord, unsigned int color)
{
	char	*pixel;

	if (color == 0xFF000000)
		return ;
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
	if (window->img)
		mlx_destroy_image(window->mlx, window->img->img);
	if (window->buf_img)
		mlx_destroy_image(window->mlx, window->buf_img->img);
	free(window->img);
	free(window->buf_img);
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

unsigned int	image_get_pixel(t_image *img, t_vec coord, int w, int h)
{
	char	*pixel;

	if (coord.x >= 0 && coord.y >= 0
		&& coord.x < w && coord.y < h)
	{
		pixel = img->addr
			+ (int)(coord.y * img->line_length + coord.x
				* (int)(img->bits_per_pixel / 8));
		if (pixel)
		{
			return (*(unsigned int *)pixel);
		}	
		else
			return (0xFF000000);
	}
	return (0xFF000000);
}
