/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeulliot <jeulliot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:05:28 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/08 13:11:00 by jeulliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <game/game.h>
# include <config/parser.h>
# include <graphics/image.h>

typedef struct s_texture {
	t_image	*img;
	int		width;
	int		height;
}	t_texture;

t_parser_state	texture_handler(t_game *game, char *line, int *i);
void			*texture_constructor(char *line, t_game *game);

#endif
