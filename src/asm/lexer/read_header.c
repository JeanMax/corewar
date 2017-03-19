/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 21:43:56 by mcanal            #+#    #+#             */
/*   Updated: 2017/03/19 20:53:10 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** read .name and .comment parts of the .s files
*/

#include "asm_lexer.h"

static void				parse_header(char *line, t_progress progress, header_t *header)
{
	static
	size_t			len;

	if (progress & P_NAME)
	{
		if ((len = ft_strlen(line)) > PROG_NAME_LENGTH)
			error(E_INVALID, "Invalid header (name too long).");
		ft_memcpy(&header->prog_name, line, len);
	}
	else if (progress & P_COMMENT)
	{
		if ((len = ft_strlen(line)) > COMMENT_LENGTH)
			error(E_INVALID, "Invalid header (comment too long).");
		ft_memcpy(&header->comment, line, len);
	}
	//TODO: count header->prog_size
}

static void				read_quoted_string(char *line)
{
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 1st quote).");
	++line;
	while (*line && *line != '"')
		line++;
	if (*line != '"')
		error(E_INVALID, "Invalid header (missing 2nd quote).");
	*line++ = 0;
	while (!IS_EOL(*line))
		if (!ft_isspace(*line++))
			error(E_INVALID, "Invalid header (weird stuffs after quotes).");
}

static t_progress		read_identifier(char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (P_NAME);
	if (!ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (P_COMMENT);

	error(E_INVALID, "Invalid header (unknown identifier)."); //TODO: it could be a 'missing header' error
	return (P_NOPROGRESS);
}

static t_progress		check_header(char *line, header_t *header)
{
	t_progress	progress;

	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;
	if (IS_EOL(*line))
		return (P_NOPROGRESS);

	progress = read_identifier(line);

	while (!IS_EOL(*line) && !ft_isspace(*line))
		line++;
	while (!IS_EOL(*line) && ft_isspace(*line))
		line++;

	read_quoted_string(line);

	parse_header(line + 1, progress, header);

	return (progress);
}

void					read_header(header_t *header)
{
	int				ret;
	char			*line;
	t_progress	progress;

	progress = P_NOPROGRESS;
	while (!(progress & P_NAME && progress & P_COMMENT))
	{
		line = NULL;
		if (!(ret = get_next_line(g_fd, &line)) || ret == -1)
			error(E_READ, NULL);

		progress |= check_header(line, header);

		ft_memdel((void **)&line);
	}

	header->magic = COREWAR_EXEC_MAGIC;
}
