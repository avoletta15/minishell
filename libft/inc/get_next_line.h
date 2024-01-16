/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:54:29 by arabelo-          #+#    #+#             */
/*   Updated: 2024/01/06 15:19:34 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*update_buffer(char *buffer, int fd);
char	*get_one_line(char *buffer);
char	*update_new_buffer(char *buffer);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif