/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:05:28 by swaegene          #+#    #+#             */
/*   Updated: 2022/06/11 15:18:41 by swaegene         ###   ########.fr       */
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

void	*texture_constructor(char *line, t_game *game);
t_bool	texture_open_images(t_game *g);
t_bool	texture_handler(char *line, t_game *game);

#endif
