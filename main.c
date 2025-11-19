/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hadia <hadia@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:42:49 by hadia             #+#    #+#             */
/*   Updated: 2025/11/19 00:49:47 by hadia            ###   ########.fr       */
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
	data->cmds = parsing(line, data->env, &data->exit_status);
	if (!data->cmds)
		return (0);
	init_envp_array(data);
	data->exit_status = exec_cmd(data, line);
	if (data->exit_status == -1)
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
	data.exit_status = 0;
	handle_signals();
	while (1)
	{
		init_data(&data, &envd);
		line = reader(&data);
		if (g_signal_status == SIG_INTERRUPTED)
		{
			data.exit_status = 130;
			g_signal_status = SIG_NONE;
		}
		if (process_line(&data, line))
			envd = data.env;
		free(line);
	}
	return (0);
}
