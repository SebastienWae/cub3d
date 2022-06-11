/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:06:43 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 15:55:20 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <game/game.h>
# include <utils/bool.h>

t_bool	map_handler(t_game *game, char *line);
void	map_normalize(t_game *game);

#endif
