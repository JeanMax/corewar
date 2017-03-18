/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/17 22:51:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H

# define ASM_PARSER_H

# include "asm.h"


/*
** instruction struct after parsing
*/
typedef struct		s_instruct_parsed
{
	t_op				*op;
	t_arg_type			arg_type[MAX_ARGS_NUMBER];
	t_dword				arg[MAX_ARGS_NUMBER];
}					t_instruct_parsed;


#endif
