/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:49 by seb               #+#    #+#             */
/*   Updated: 2022/05/31 11:51:20 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <utils/bool.h>
# include <libft.h>
# include <config/config.h>
# include <graphics/window.h>
# include <game/player.h>
// TODO: remove
# include <stddef.h>

typedef struct s_coordonate
{
	size_t	x;
	size_t	y;
}	t_coordonate;

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

void	game_destructor(t_game *game);
t_game	*game_constructor(void);
t_game	*game_init(char *config_file_path);
void	game_start_loop(t_game *game);

#endif
