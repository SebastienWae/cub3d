/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:11:41 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/29 14:46:21 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <bool.h>
#include <stdlib.h>
#include <window/window.h>

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
	mlx_destroy_window(window->mlx, window->win);
	free(window->mlx);
	*window = (t_window){.mlx = NULL, .win = NULL, .open = FALSE};
	free(window);
}

t_window	*window_constructor(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
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
	window->open = TRUE;
	if (!window->win)
	{
		free(window->mlx);
		free(window);
		return (NULL);
	}
	mlx_hook(window->win, ON_DESTROY, 0, window_close, window);
	mlx_key_hook(window->win, window_esc, window);
	return (window);
}
