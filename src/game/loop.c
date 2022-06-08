/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:30 by seb               #+#    #+#             */
/*   Updated: 2022/06/08 15:41:06 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>
#include <game/game.h>
#include <game/movements.h>
#include <game/door.h>
#include <graphics/walls.h>
#include <graphics/minimap.h>
#include <graphics/render.h>
#include <graphics/window.h>
#include <graphics/image.h>
#include <utils/bool.h>

#include <math.h>

static int	loop_hook(t_game *game)
{
	if (!game->window->open)
	{
		game_destructor(game);
		exit(EXIT_SUCCESS);
	}
	rotate(game);
	move(game);
	if (game->window->redraw)
	{
		render(game);
		minimap_draw(game);
		mlx_put_image_to_window(game->window->mlx, game->window->win,
			game->window->img->img, 0, 0);
		image_destructor(game->window);
		game->window->img = image_constructor(game->window, NULL);
		game->window->redraw = FALSE;
	}
	return (0);
}

static t_key_id	get_key_id(int keycode)
{
	if (keycode == KEY_LEFT)
		return (LEFT);
	else if (keycode == KEY_RIGHT)
		return (RIGHT);
	else if (keycode == KEY_W)
		return (W);
	else if (keycode == KEY_A)
		return (A);
	else if (keycode == KEY_S)
		return (S);
	else if (keycode == KEY_D)
		return (D);
	return (ERR_KEY);
}

static int	loop_keydown(int keycode, t_game *game)
{
	t_key_id	id;

	if (keycode == KEY_ESC)
	{
		window_close(game->window);
		return (0);
	}
	if (keycode == KEY_SPACE)
	{
		door_toggle(game);
		return (0);
	}
	id = get_key_id(keycode);
	if (id != ERR_KEY)
		game->window->active_keys[id] = TRUE;
	return (0);
}

static int	loop_keyup(int keycode, t_game *game)
{
	t_key_id	id;

	if (keycode == KEY_ESC)
		window_close(game->window);
	id = get_key_id(keycode);
	if (id != ERR_KEY)
		game->window->active_keys[id] = FALSE;
	return (0);
}

static int	loop_mouse_down(int button, int x, int y, t_game *game)
{	
	if (button == 1 && y > 0 && y < WINDOW_HEIGHT)
	{
		if(x <  WINDOW_WIDTH / 2)
			{
				game->window->active_keys[0] = TRUE;
				game->window->active_keys[1] = FALSE;
			}
		else if (x >  WINDOW_WIDTH / 2)
			{
				game->window->active_keys[1] = TRUE;
				game->window->active_keys[0] = FALSE;
			}
	}
	return(0);
}

static int	loop_mouse_up(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	(void) button;
	game->window->active_keys[0] = FALSE;
	game->window->active_keys[1] = FALSE;
	return (0);
}

void	loop_start(t_game *game)
{	
	mlx_hook(game->window->win, ON_DESTROY, 0, window_close, game->window);
	mlx_hook(game->window->win, ON_KEYDOWN, (1L << 0), loop_keydown, game);
	mlx_hook(game->window->win, ON_KEYUP, (1L << 1), loop_keyup, game);
	mlx_hook(game->window->win, ON_MOUSEDOWN, 0, loop_mouse_down, game);
	mlx_hook(game->window->win, ON_MOUSEUP, 0, loop_mouse_up, game);
	mlx_loop_hook(game->window->mlx, loop_hook, game);
	mlx_loop(game->window->mlx);
}
