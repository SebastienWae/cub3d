/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:06:43 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/09 20:41:10 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <game/game.h>
# include <config/parser.h>

t_parser_state	map_handler(t_game *game, char *line, int *i);
void			map_normalize(t_game *game);

#endif
