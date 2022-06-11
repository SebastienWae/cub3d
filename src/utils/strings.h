/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:12:21 by seb               #+#    #+#             */
/*   Updated: 2022/06/11 15:08:23 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

# define BUFFER_SIZE 1000

# include <utils/bool.h>

int		array_size(void **array);
int		is_in_array(char **array, int lenght, char *str);
char	*get_next_line(int fd);
t_bool	is_empty(char *str);

#endif
