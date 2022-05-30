/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:12:24 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 15:12:54 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include <mlx.h>
# include <bool.h>

# define WINDOW_NAME "cub3d"
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512

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
// TODO: verify keycode (esc is ok)
enum {
	KEY_ESC = 65307,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
};

# elif __APPLE__

enum {
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_UP = 126,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
};

# endif

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
	t_bool	open;

}	t_window;

t_window	*window_constructor(void);
void		window_destructor(t_window *window);

#endif
