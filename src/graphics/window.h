/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:12:24 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/10 14:34:14 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>
# include <libft.h>
# include <utils/bool.h>

# define WINDOW_NAME "cub3d"
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_W = 13,
	KEY_A = 0,
	KEY_D = 2,
	KEY_S = 1,
	KEY_SPACE = 49
};

typedef enum e_key_id
{
	LEFT,
	RIGHT,
	W,
	S,
	A,
	D,
	ERR_KEY
}	t_key_id;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_image	*img;
	t_image	*buf_img;
	t_bool	redraw;
	t_bool	open;
	t_bool	active_keys[6];
}	t_window;

t_window	*window_constructor(void);
void		window_destructor(t_window *window);
int			window_close(t_window *window);
void		window_swap_image(t_window *window);

#endif
