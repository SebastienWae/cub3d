/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:06:43 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/31 21:20:57 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <game/game.h>
# include <config/parser.h>
# include <utils/bool.h>

t_parser_state	map_handler(t_game *game, char *line, int *i);
void			map_get_scale(t_game *game);

#endif
