/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:25:02 by seb               #+#    #+#             */
/*   Updated: 2022/06/09 17:35:42 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_error_action
{
	ADD,
	ADD_NO_NL,
	FLUSH
}	t_error_action;

void	error_msg(char *msg, t_error_action action);

#endif
