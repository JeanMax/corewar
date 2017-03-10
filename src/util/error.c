/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/10 17:00:33 by mcanal           ###   ########.fr       */
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

void			error(t_uint flag, char *msg)
{
	const char	*error[] = {
		": Too many args.",
		": Ouch... can't read this.",
		": What the heck is that file? Nah, just try with something else. - ",
		": Dang. SDL couldn't make it... ",
		": Damn... Looks like I can't even open a window."
	};

	fail(g_exec_name);
	if (msg)
	{
		fail(error[get_index(flag & (t_uint)~E_NOEXIT)]);
		failn(msg);
	}
	else
		failn(error[get_index(flag & (t_uint)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
	{
		/* SDL_Quit(); //TODO: check how it's handled if SDL wasn't launched */
		exit(EXIT_FAILURE);
	}
}
