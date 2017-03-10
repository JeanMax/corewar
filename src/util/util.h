/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/10 17:01:39 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H

# define UTIL_H

# include "libft.h"

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE = (1 << 1),
	E_READ = (1 << 2),
	E_INVALID = (1 << 3),
	E_SDLINIT = (1 << 4),
	E_SDLSETVIDEO = (1 << 5),
};

/*
** globad
*/
extern char				*g_exec_name;

/*
** error.c
*/
void					error(t_uint flag, char *msg);

#endif
