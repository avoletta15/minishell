/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:32:32 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/14 09:49:25 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function writes to the write end of the here_doc pipe.
/// and closes the write end of the pipe. It exits with success.
/// @param line 
/// @param delimiter 
/// @param fd 
/// @param sigint 
void	here_doc_write_loop(char *line, char *delimiter, int fd, bool *sigint)
{
	while (1)
	{
		write(STDERR_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			*sigint = get_terminal()->hd_exit;
			if (!*sigint)
				here_doc_ctrl_d(delimiter);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

/// @brief This function removes the ECHOCTL flag from the here_doc terminal.
/// @param term 
/// @param original 
/// @param sigint 
void	remove_echoctl(struct termios *term,
		struct termios *original, bool *sigint)
{
	(void)original;
	if (tcgetattr(STDOUT_FILENO, term) == 0)
	{
		original = term;
		term->c_lflag &= ~(ECHOCTL);
		tcsetattr(STDOUT_FILENO, TCSANOW, term);
	}
	*sigint = false;
}
