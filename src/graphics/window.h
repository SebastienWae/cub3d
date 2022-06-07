/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:12:24 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/07 19:56:52 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>
# include <libft.h>
# include <utils/bool.h>

# define WINDOW_NAME "cub3d"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# ifdef __linux__

enum {
	KEY_ESC = 65307,
	KEY_LEFT = 65361,
	KEY_UP = 65362,
	KEY_RIGHT = 65363,
	KEY_DOWN = 65364,
	KEY_W = 119,
	KEY_A = 97,
	KEY_D = 100,
	KEY_S = 115
};

# elif __APPLE__

enum {
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_W = 13,
	KEY_A = 0,
	KEY_D = 2,
	KEY_S = 1
};

# endif

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
	t_bool	redraw;
	t_bool	open;
	t_bool	active_keys[6];
}	t_window;

t_window	*window_constructor(void);
void		window_destructor(t_window *window);
int			window_close(t_window *window);

#endif
