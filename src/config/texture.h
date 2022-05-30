/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:05:28 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/30 14:52:35 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <config/config.h>
# include <graphics/window.h>

t_parser_state	config_handle_texture(t_config *conf, char *line, int *i,
					t_window *window);

#endif
