/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebroue <leobroue@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:42:49 by hadia             #+#    #+#             */
/*   Updated: 2025/11/15 00:34:51 by lebroue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_and_exit(t_data *data, char *line, int status)
{
	free(line);
	rl_clear_history();
	free_envp(data->envp);
	free_cmds(data->cmds);
	free_lst_env(&data->env, true, 0);
	exit(status);
}

static int	process_line(t_data *data, char *line)
{
	if (!line || line[0] == '\0')
		return (0);
	add_history(line);
	data->cmds = parsing(line, data->env);
	if (!data->cmds)
		return (0);
	init_envp_array(data);
	g_exit_status = exec_cmd(data, line);
	if (g_exit_status == -1)
		cleanup_and_exit(data, line, 1);
	free_cmds(data->cmds);
	free_envp(data->envp);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*envd;
	t_data	data;

	(void)ac;
	(void)av;
	envd = NULL;
	init_lst_env(&envd, env);
	save_std_in_out(&data);
	handle_signals();
	while (1)
	{
		init_data(&data, &envd, NULL);
		line = reader(&data);
		if (process_line(&data, line))
			envd = data.env;
		free(line);
	}
	return (0);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	int		i;
	t_redir	*r_tmp;

	tmp = cmds;
	while (tmp)
	{
		printf("Command: %s\n", tmp->name);
		if (tmp->args)
		{
			i = 0;
			printf("Arguments:\n");
			while (tmp->args[i])
			{
				printf("  arg[%d]: %s\n", i, tmp->args[i]);
				i++;
			}
		}
		else
		{
			printf("No arguments\n");
		}
		if (tmp->redirs)
		{
			r_tmp = tmp->redirs;
			printf("Redirections:\n");
			while (r_tmp)
			{
				printf("  Type: %d, File: %s\n", r_tmp->type, r_tmp->file);
				r_tmp = r_tmp->next;
			}
		}
		else
		{
			printf("No redirections\n");
		}
		tmp = tmp->next;
	}
}

void	print_lst_env(t_env *envd)
{
	t_env	*current;

	current = envd;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token *current = tokens;
	while (current)
	{
		printf("Token Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}