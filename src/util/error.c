/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 00:23:58 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** errors handling
** first arg is a flag including enums e_error (cf .h) (ex: E_OPEN | E_NOEXIT)
** second arg is an optionnal error message
*/

#include "util.h"
#include <stdlib.h>

/*
** I'm pretty sure there is another way...
*/
static int		get_index(t_uint flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

t_bool			error(t_uint flag, char *msg)
{
	const char	*error[] = {
		" [-dump NBR_CYCLES] [[-n NUMBER] FILE.cor]...",
		" FILE.s",
		": Ouch... can't read this.",
		": Damn! Can't open file: ",
		": Dang. Can't close file: ",
		": What the heck is that file? Nah, just try with something else. - "
	};

	if (flag & E_USAGE_COREWAR || flag & E_USAGE_ASM)
		fail("Usage: ");
	fail(g_exec_name);
	if (msg)
	{
		fail(error[get_index(flag & (t_uint)~E_NOEXIT)]);
		failn(msg);
	}
	else
		failn(error[get_index(flag & (t_uint)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
		exit(EXIT_FAILURE);
	return (FALSE);
}
