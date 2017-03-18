/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/17 23:19:47 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** parse .s files
*/

#include "asm_parser.h"

/* static void				debug_type(t_arg_type type) */
/* { */
/* 	if (type & T_REG) */
/* 		ft_debugstr("type", "T_REG"); */
/* 	if (type & T_DIR) */
/* 		ft_debugstr("type", "T_DIR"); */
/* 	if (type & T_IND) */
/* 		ft_debugstr("type", "T_IND"); */
/* 	if (type & T_LAB) */
/* 		ft_debugstr("type", "T_LAB"); */
/* } */


/* static t_arg_type		check_arg_type(char *arg) */
/* { */
/* 	int			i; */
/* 	t_arg_type	ret; */

/* 	ret = T_IND; */
/* 	if (*arg == 'r') */
/* 	{ */
/* 		i = ft_atoi(++arg); */
/* 		if (i < 1 || i > REG_NUMBER) */
/* 			error(E_INVALID, "Invalid register (REG_NUMBER not in range)."); */
/* 		ret = T_REG; */
/* 	} */
/* 	else if (*arg == DIRECT_CHAR && ++arg) */
/* 		ret = T_DIR; */

/* 	if (*arg == LABEL_CHAR && ret != T_REG) */
/* 		return (T_LAB | ret); //TODO: check if label exists, eventually after... */
/* 	while (*arg) */
/* 		if (!ft_isdigit(*arg++)) */
/* 			error(E_INVALID, "Invalid arg (not a number)."); */
/* 	return (ret); */
/* } */

/* static enum e_progress	read_arg(char *arg, size_t len) */
/* { */
/* 		*(instruct.arg_type + arg_count) = \ */
/* 			check_arg_type(*(instruct.arg + arg_count)); */

/* 		if (!(*(instruct.arg_type + arg_count) & ~T_LAB) &	\ */
/* 				*(instruct.op->arg_type + arg_count)) */
/* 			error(E_INVALID, "Invalid arg (wrong arg type)."); */

/* 	if (arg_count != instruct.op->arg_count) */
/* 		error(E_INVALID, "Invalid arg (wrong number)."); */
/* 	return (P_ARG); */
/* } */




	//TODO: parse_op:
	/* t_op	*op_tab_swap; */

	/* op_tab_swap = op_tab; */
	/* while (op_tab_swap->name && ft_memcmp(op_tab_swap->name, op, len)) */
	/* 	op_tab_swap++; */
	/* if (!op_tab_swap->name) */
	/* 	error(E_INVALID, "Invalid op (not found)."); */
	/* instruct.op = op_tab_swap; */
