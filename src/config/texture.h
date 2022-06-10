/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:05:28 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/10 14:08:09 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <game/game.h>
# include <config/parser.h>
# include <config/config.h>
# include <graphics/window.h>

typedef struct s_texture {
	t_image	*img;
	int		width;
	int		height;
}	t_texture;

t_parser_state	texture_handler(t_game *game, char *line, int *i);
void			*texture_constructor(char *line, t_game *game);
t_bool			texture_open_images(t_game *g);

#endif
