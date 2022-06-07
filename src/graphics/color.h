/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:28:27 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 20:29:26 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int	color_shade(int trbg, int shade);
int	color_get_t(int trgb);
int	color_get_r(int trgb);
int	color_get_b(int trgb);
int	color_get_g(int trgb);

#endif
