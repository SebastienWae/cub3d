/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seb <seb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:24:05 by seb               #+#    #+#             */
/*   Updated: 2022/06/07 20:28:17 by seb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	color_get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	color_get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	color_get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	color_get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	color_shade(int trbg, int shade)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = color_get_t(trbg);
	r = color_get_r(trbg);
	if (r < shade)
		r = 0;
	else
		r -= shade;
	b = color_get_b(trbg);
	if (b < shade)
		b = 0;
	else
		b -= shade;
	g = color_get_g(trbg);
	if (g < shade)
		g = 0;
	else
		g -= shade;
	return (t << 24 | r << 16 | g << 8 | b);
}
