/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:40:19 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/01/20 19:34:39 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* dar handle do que é permitido, ao inves do que nao pode */

bool	ft_forbidden_expansion(char c, int i)
{
	if ((ft_isalpha(c) || c == '_') && i == 1)
		return (false);
	else if (ft_isalnum(c) || c == '_')
		return (false);
	return (true);
}

char	*variable_alias(char *str)
{
	char	*expand_var;
	int		i;

	i = 0;
	while(str[++i])
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
char	*ft_search_variable(char *var, t_terminal terminal)
{
	while (terminal.env->next)
	{
		if (!ft_strncmp(var, terminal.env->info, ft_strlen(var)))
			break ;
		terminal.env->next;
	}
	if (!terminal.env)
		return(ft_strdup(""));
	return (ft_strdup(terminal.env->info + (ft_strlen(var) + 1)));
}

char	*ft_should_expand(char *str, int *i, t_terminal terminal)
{
 	char	*expand_var;
	
	expand_var = variable_alias(&str[*i]);
	if (ft_strncmp(expand_var, "$", ft_strlen("$")))
	{
		expand_var = ft_search_variable(expand_var, terminal);
		if (!expand_var)
		{
			// free
			return (NULL);
		}
		*i += ft_strlen(expand_var) + 1; /* verificar se precisa mesmo do +1 */
	}
	else
		*i += 1;
	if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
		expand_var = ft_itoa(terminal.exit_status);
	return (expand_var);
	
}

char	*ft_expansion_check(t_terminal terminal, int flag)
{
	int			i;
	char		*var_key;
	char		*temp;

	var_key = ft_strdup(terminal.tokens->token);
	i = 0;
	while (terminal.tokens->token[i])
	{
		if (terminal.tokens->token[i] == SINGLE_QUOTE || \
			terminal.tokens->token[i] == DOUBLE_QUOTE)
		{
			if (!flag)
				flag = 1;
			else	
			 /* verificar se nao tem de ser char */;
		}
		if (flag == 1 || terminal.tokens->token[i] != '$')
		{
			i++;
			continue ;
		}
		temp = ft_substr(var_key, 0, i);
		free(var_key);
		temp = ft_strjoin(temp, ft_should_expand(terminal.tokens->token, &i, terminal));
		var_key = ft_strjoin(temp, ft_substr(terminal.tokens->token, i, ft_strlen(terminal.tokens->token)));
		
	}
	//free??????
	return (var_key);
}
