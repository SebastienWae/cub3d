/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:49 by seb               #+#    #+#             */
/*   Updated: 2022/05/30 15:56:50 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <bool.h>
# include <libft.h>
# include <config/config.h>
# include <graphics/window.h>
# include <graphics/image.h>

typedef struct s_coordonate
{
	int	x;
	int	y;
}	t_coordonate;

typedef struct s_player
{
	t_coordonate	position;
	double			direction;
}	t_player;

typedef struct s_door
{
	t_bool			open;
	t_coordonate	position;
}	t_door;

typedef struct s_game
{
	t_config	*config;	
	t_window	*window;
	t_player	*player;
	t_list		*doors;
}	t_game;

#endif
