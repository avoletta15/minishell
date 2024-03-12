/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:24:07 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/03/11 19:14:23 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief This function searchs for chars that are
/// not allowed to form variables' names.
/// @param c 
/// @param i 
/// @return 
bool	ft_forbidden_expansion(char c, int i)
{
	if ((ft_isalpha(c) || c == '_') && i == 1)
		return (false);
	else if ((ft_isalnum(c) || c == '_') && i > 1)
		return (false);
	return (true);
}

/// @brief This function searchs for the HOME directory's
/// path using getcwd() function.
/// @return 
char	*ft_get_home()
{
	int		count;
	int		p;
	char	*home;
	char	*path;

	p = 0;
	count = 1;
	path = getcwd(NULL, 0);
	home = (char *)malloc(sizeof(char) * ft_strlen(path) + 1);
	if (!home)
		return (NULL);
	while(path && path[p])
	{
		if(path[p] == '/' && p != 0)
			count++;
		if(count == 3)
			break;
		home[p] = path[p];
		p++;
	}
	free(path);
	return(home);
}

/// @brief This function checks if the variable after the $
/// is formed by valide chars.
/// @param str 
/// @return 
char	*variable_alias(char *str)
{
	char	*expand_var; 
	int		i;

	i = 0;
	while(str && str[++i])
	{
		if((str[i] == '?' && i == 1) || ft_forbidden_expansion(str[i], i) == true)
			break ;
	}
	if (i == 1 && str[i - 1] == '$' && str[i] != '?')
		expand_var = ft_strdup("$");
	else if (i == 1 && str[i])
		expand_var = ft_substr(str, 1, i);
	else
		expand_var = ft_substr(str, 1, (i - 1));
	return(expand_var);

}