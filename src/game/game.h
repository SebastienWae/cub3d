/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:45:49 by seb               #+#    #+#             */
/*   Updated: 2022/06/08 23:29:13 by jenny            ###   ########.fr       */
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
	t_list		*doors;
}	t_game;

void	game_destructor(t_game *game);
t_game	*game_constructor(void);
t_game	*game_init(char *config_file_path);
void	game_start_loop(t_game *game);

#endif
