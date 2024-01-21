/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:40:19 by mariaavolet       #+#    #+#             */
/*   Updated: 2024/01/21 18:50:28 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*ft_search_variable(char *var, t_terminal *terminal)
{
	t_env	*env;

	env = terminal->env;
	while (env->next)
	{
		if (!ft_strncmp(var, env->info, ft_strlen(var)))
			break ;
		env = env->next;
	}
	if (!env)
		return(ft_strdup(""));
	return (ft_strdup(env->info + (ft_strlen(var) + 1)));
}

char	*ft_should_expand(char *str, int *i, t_terminal *terminal)
{
 	char	*expand_var;
	
	expand_var = variable_alias(&str[*i]);
	if (ft_strncmp(expand_var, "$", ft_strlen("$")))
	{
		*i += ft_strlen(expand_var) + 1;
		expand_var = ft_search_variable(expand_var, terminal);
		if (!expand_var)
		{
			free(expand_var);
			free(terminal->prompt);
			malloc_error();
			exit(EXIT_FAILURE);
			return (NULL);
		}
	}
	else
		*i += 1;
	if (!ft_strncmp(expand_var, "?", ft_strlen("?")))
		expand_var = ft_itoa(terminal->exit_status);
	return (expand_var);
	
}

char	ft_checking_quotes(char c, char flag)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
	{
		if (!flag)
			flag = c;
		else
			flag = '\0';
	}
	return (flag);
}

char	*ft_join_free(char *test, int i, char *temp, t_terminal *terminal)
{
	char	*var_key;
	free(temp);
	temp = test;
	var_key = ft_strjoin(temp, ft_substr(terminal->tokens->token, i, ft_strlen(terminal->tokens->token)));
	return(var_key);
}

char	*ft_expansion_check(t_terminal *terminal, char flag)
{
	int			i;
	char		*var_key;
	char		*temp;
	char		*new_index;
	char		*test;

	new_index = 0;
	var_key = ft_strdup(terminal->tokens->token); //**$USER
	i = 0;
	while (terminal->tokens && terminal->tokens->token[i])
	{
		flag = ft_checking_quotes(terminal->tokens->token[i], flag);
		if (flag == SINGLE_QUOTE || terminal->tokens->token[i] != '$')
		{
			i++;
			continue ;
		}
		temp = ft_substr(var_key, 0, ft_strlen(new_index));
		new_index = ft_should_expand(terminal->tokens->token, &i, terminal);
		test = ft_strjoin(temp, new_index);
		var_key = ft_join_free(test, i, temp, terminal);
	}
	return (var_key);
}
