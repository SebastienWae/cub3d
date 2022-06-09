/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:21:07 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 15:44:17 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <game/game.h>
# include <utils/bool.h>

enum {
	HEIGHT,
	WIDTH
};

enum {
	IN_WALL,
	PLAYER
};

typedef enum e_parser_state
{
	CP_S_TEXTURES = 1,
	CP_S_COLORS,
	CP_S_MAP,
	CP_S_DONE,
	CP_S_ERROR
}	t_parser_state;

t_bool	parse_config_file(int fd, t_game *game);
t_bool	parse_map(t_game *game);

t_bool	map_space_handler(t_game *game, size_t c[2], t_bool s[2]);
t_bool	map_zero_handler(t_game *game, size_t c[2], t_bool s[2]);
t_bool	map_player_handler(t_game *game, size_t c[2], t_bool s[2]);
t_bool	map_door_handler(t_game *game, size_t c[2], t_bool s[2]);

void	parse_player(t_game *game, size_t c[2]);

#endif
