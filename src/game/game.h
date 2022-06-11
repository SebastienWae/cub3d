/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 13:48:08 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <libft.h>
# include <config/config.h>
# include <graphics/window.h>
# include <game/player.h>
# include <utils/bool.h>
# include <utils/vec.h>

# define PLAYER_MINIMAP_TEXTURE "./assets/arrow.png"
# define DOOR_CLOSE_TEXTURE "./assets/curtain.xpm"
# define DOOR_OPEN_TEXTURE "./assets/curtain_open.xpm"

typedef struct s_door
{
	t_bool	open;
	t_vec	position;
}	t_door;

typedef struct s_game
{
	t_config	*config;	
	t_window	*window;
	t_player	*player;
}	t_game;

t_game	*game_init(char *config_file_path);
void	game_destructor(t_game *game);
void	game_start_loop(t_game *game);

#endif
