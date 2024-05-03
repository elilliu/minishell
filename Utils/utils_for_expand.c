/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:51:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/05/03 18:00:36 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	return (i);
}

char	*copy_str(char *str, int size)
{
	char	*newstr;

	newstr = malloc(sizeof(char) * (size + 1));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, str, size + 1);
	return (newstr);
}

void	init_expand(t_expand *expand)
{
	expand->before = NULL;
	expand->expand = NULL;
	expand->after = NULL;
}

void	free_expand(t_expand *expand)
{
	if (expand->before)
		free(expand->before);
	if (expand->expand)
		free(expand->expand);
	if (expand->after)
		free(expand->after);
}
