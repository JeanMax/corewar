/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/20 00:35:48 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H

# define UTIL_H

# include "libft.h"
# include "op.h"

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE_COREWAR = (1 << 1),
	E_USAGE_ASM = (1 << 2),
	E_READ = (1 << 3),
	E_OPEN = (1 << 4),
	E_CLOSE = (1 << 5),
	E_INVALID = (1 << 6),
	E_WRITE = (1 << 7)
};

typedef unsigned char			t_byte;
typedef unsigned short			t_word;
typedef unsigned int			t_dword;

/*
** globad
*/
extern char				*g_exec_name;
extern int				g_fd;

/*
** error.c
*/
t_bool					error(t_uint flag, char *msg);

#endif
