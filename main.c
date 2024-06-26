/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:27:31 by oszwalbe          #+#    #+#             */
/*   Updated: 2024/05/03 18:25:26 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	do_simple_command(t_set *set)
// {
// 	int	id;

// 	id = fork();
// 	if (id == 0)
// 	{
// 		execute_command(set->cmd, set->env);
// 	}
// 	while (wait(NULL) != -1)
// 		continue ;
// }

int	check_pipe(t_set *set)
{
	int	i;

	i = 0;
	while (set->cmd[i])
	{
		if (ft_strcmp(set->cmd[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	executable(t_set *set)
{
	int	j;

	j = 0;
	if (check_pipe(set))
		parse_for_pipe(set);
	else if (ft_strcmp("echo", set->cmd[0]) == 0)
		echo_command(set->cmd + 1);
	else if (ft_strcmp("cd", set->cmd[0]) == 0)
		cd_command(set->cmd[1]);
	else if (ft_strcmp("pwd", set->cmd[0]) == 0)
		pwd_command(set->cmd);
	else if (ft_strcmp("env", set->cmd[0]) == 0)
		env_command(set->cmd, set->env);
	else if (ft_strcmp("exit", set->cmd[0]) == 0)
		exit_command(set->cmd[1], set->size_tab);
	else if (ft_strcmp("unset", set->cmd[0]) == 0)
		unset_command(set, set->env);
	else
	{
		do_simple_command(set);
	}
}

void	parse_for_pipe(t_set* set)
{
	char ***c;
	int	i;
	int j;

	i = 0;
	j = 0;
	print_tab(set->cmd);
	c = copy_of_tab_of_tab(set, set->cmd);
	while (c[i])
	{
		printf("\nCase %d :\n", i);
		j = 0;
		while (c[i][j])
		{
			printf("-> : %s\n", c[i][j]);
			j++;
		}
		i++;
	}
	free_tab(c[0]);
	free_tab(c[1]);
	free(c);
}

int	main(int ac, char **av, char **env)
{
	t_set	set;
	int		i;

	(void)av;
	(void)env;
	if (ac < 1)
		return (1);
	i = 0;
	set.env = copy_of_tab(env);
	while (1)
	{
		set.input = readline("\1\033[38;5;226m\2M\1\033[38;5;220m\2i\1\033[38;5;214m\2"
								"n\1\033[38;5;208m\2i\1\033[38;5;202m\2S\1\033[38;5;196m\2"
								"c\1\033[38;5;202m\2h\1\033[38;5;208m\2w\1\033[38;5;214m\2"
								"e\1\033[38;5;220m\2p\1\033[38;5;226m\2p\1\033[38;5;220m\2"
								"e\1\033[38;5;214m\2s\1\033[38;5;208m\2 \1\033[38;5;208m\2"
								">\1\033[0m ");
		if (set.input == NULL)
		{
			break ;
		}
		set.cmd = NULL;
		if (ft_occurence(set.input) != ft_strlen(set.input))
		{
			add_history(set.input);
			set.i = 0;
			set.cmd = parse(&set);
			if (expand(&set) == 0)
				break;
		}
		if (set.cmd)
		{
			set.size_tab = tab_calculate(set.cmd);
			executable(&set);
			// exec(&set);
			free_tab(set.cmd);
		}
		free(set.input);
	}
	free_tab(set.env);
	clear_history();
	return (0);
}
