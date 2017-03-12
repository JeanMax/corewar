/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/12 21:48:16 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_PARSER_H

# define ASM_PARSER_H

# include "asm.h"

#include "op.h"

/*
** open
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** read / close
*/
# include <unistd.h>

# define IS_EOL(c) (!c || c == COMMENT_CHAR)

/*
** parsing progress enum
*/
enum					e_progress
{
	P_NOPROGRESS = 0,
	P_LABEL = (1 << 0),
	P_OP = (1 << 1),
	P_ARG = (1 << 2),
};

/*
** parse_header.c
*/
void					read_header(int fd, char *cmd_string);

/*
** parse_instruction.c
*/
void					read_loop(int fd);

#endif
