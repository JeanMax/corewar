/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/18 00:53:00 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_LEXER_H

# define ASM_LEXER_H

# include "asm.h"

# define IS_EOL(c) (!c || c == COMMENT_CHAR)
# define MAX_ARG_LENGTH		(MAX_LABEL_LENGTH + 3)
# define MAX_LABEL_LENGTH	23
# define MAX_OP_CODE_LENGTH	7


/*
** lexing progress enum
*/
enum					e_progress
{
	P_NOPROGRESS = 0,
	P_NAME = (1 << 0),
	P_COMMENT = (1 << 1),
	P_LABEL = (1 << 2),
	P_OP = (1 << 3),
	P_ARG = (1 << 4),
};

/*
** instruction struct as read
*/
typedef struct		s_instruct_read
{
	char				label[MAX_LABEL_LENGTH + 1];
	char				op[MAX_OP_CODE_LENGTH + 1];
	int					argc;
	char				argv[MAX_ARGS_NUMBER][MAX_ARG_LENGTH + 1];
}					t_instruct_read;

/*
** read_header.c
*/
void					read_header(int fd);

/*
** read_instruction.c
*/
void					read_loop(int fd);

#endif
