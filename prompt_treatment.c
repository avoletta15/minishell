/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_treatment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:21:05 by arabelo-          #+#    #+#             */
/*   Updated: 2023/12/20 15:50:08 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_replace(char *str, t_quotes_system *quotes_system)
{
	char	*replaced;
	size_t	i;

	i = 0;
	replaced = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!replaced)
		return (NULL);
	while (str[i])
	{
		if (ft_isspace(str[i]) && !quotes_system->quotes_state)
			replaced[i] = '\2';
		// else if (ft_isspace(str[i]) && quotes_system->quotes_state)
		else
			replaced[i] = str[i];
		i++;
	}
	return (replaced);
}