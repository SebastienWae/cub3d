/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:11:41 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 17:20:30 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils/bool.h>
#include <stdlib.h>
#include <graphics/window.h>
#include <graphics/image.h>

static int	window_close(t_window *window)
{
	window->open = FALSE;
	return (0);
}

static int	window_esc(int keycode, t_window *window)
{
	if (keycode && keycode == KEY_ESC)
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
	window->win = mlx_new_window(window->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_NAME);
	window->img = image_constructor(window);
	if (!window->win || !window->img)
	{
		window_destructor(window);
		return (NULL);
	}
	window->open = TRUE;
	mlx_hook(window->win, ON_DESTROY, 0, window_close, window);
	mlx_key_hook(window->win, window_esc, window);
	return (window);
}
