/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:11:41 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/03 14:41:40 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <libft.h>
#include <stdlib.h>
#include <graphics/window.h>
#include <graphics/image.h>

int	window_close(t_window *window)
{
	window->open = FALSE;
	return (0);
}

void	window_destructor(t_window *window)
{
	if (window->img)
		image_destructor(window);
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
	*window = (t_window){.mlx = NULL, .win = NULL, .img = NULL, .open = FALSE};
	free(window);
}

t_window	*window_constructor(void)
{
	t_window	*window;

	window = ft_calloc(1, sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init();
	if (!window->mlx)
	{
		free(window);
		return (NULL);
	}
	window->redraw = TRUE;
	return (window);
}
