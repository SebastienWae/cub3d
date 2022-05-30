/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:06:43 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 17:20:50 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <config/config.h>
# include <utils/bool.h>

enum {
	HEIGHT,
	WIDTH
};

enum {
	IN_WALL,
	PLAYER
};

t_parser_state	config_handle_map(t_config *conf, char *line, int *i);
t_bool			config_map_is_valid(t_config *config);

t_bool			map_space_handler(t_config *conf, size_t c[2], t_bool s[2]);
t_bool			map_zero_handler(t_config *conf, size_t c[2], t_bool s[2]);
t_bool			map_player_handler(t_config *conf, size_t c[2], t_bool s[2]);
t_bool			map_door_handler(t_config *conf, size_t c[2], t_bool s[2]);

#endif
