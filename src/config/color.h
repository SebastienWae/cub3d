/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:02:44 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/31 11:16:42 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <game/game.h>
# include <config/parser.h>

t_parser_state	color_handler(t_game *game, char *line, int *i);

#endif
