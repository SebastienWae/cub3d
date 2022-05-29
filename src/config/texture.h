/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:05:28 by swaegene          #+#    #+#             */
/*   Updated: 2022/05/29 11:12:43 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include <config/config.h>
# include <window/window.h>

t_parser_state	config_handle_texture(t_config *conf, char *line, int *i,
					t_window *window);

#endif
